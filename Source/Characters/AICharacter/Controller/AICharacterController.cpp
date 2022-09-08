// Copyright Epic Games, Inc. All Rights Reserved.


#include "AICharacterController.h"

#include "Types.h"
#include "BaseCharacter.h"
#include "AICharacter/AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

void AAICharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (!Character.IsValid())
		return;
	
	InitControlling(Character -> GetTargetPositionToMove(), Character -> GetBehaviorTree());
}

void AAICharacterController::InitControlling(FVector TargetPosition, UBehaviorTree* BehaviorTree)
{
	APosition = Character -> GetActorLocation();
	APosition.Z -= Character -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight();
	BPosition = TargetPosition;
	
	RunBehaviorTree(BehaviorTree);
	Blackboard -> SetValueAsVector(BB_NextLocation, BPosition);
	BrainComponent -> StartLogic();
	if (Character -> GetMovementInfo().NeedSplitMovementByParts)
		FirstPartMovement();
}

void AAICharacterController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (IsValid(InPawn))
	{
		checkf(InPawn -> IsA<ABaseCharacter>(), TEXT("Only ABaseCharacter"));
		Character = StaticCast<AAICharacter*>(InPawn);
		return;
	}

	Character = nullptr;
}

void AAICharacterController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
	if (!Result.IsSuccess())
		return;

	Character -> PlayFinishReachedSound();
	Character -> ExecuteEffect();
	Destroy();
}

void AAICharacterController::FirstPartMovement()
{
	const FMovementInfo MovementInfo = Character -> GetMovementInfo();
	DoActions(MovementInfo.FirstPartMovementActions);
	
	GetWorld() -> GetTimerManager().SetTimer(SecondPartMovementTimer, this,
		&AAICharacterController::SecondPartMovement, MovementInfo.FirstPartMovementTime, false);
}

void AAICharacterController::SecondPartMovement()
{
	const FMovementInfo MovementInfo = Character -> GetMovementInfo();
	DoActions(MovementInfo.SecondPartMovementActions);

	GetWorld() -> GetTimerManager().SetTimer(FirstPartMovementTimer, this,
		&AAICharacterController::FirstPartMovement, MovementInfo.SecondPartMovementTime, false);
}

void AAICharacterController::DoActions(EActionsTypes ActionsTypes)
{
	switch (ActionsTypes)
	{
		case EActionsTypes::EA_Movement:
			{
				if (WasBackMovementBeen)
				{
					if (!IsMoveToBPosition)
					{
						Blackboard -> SetValueAsVector(BB_NextLocation, BPosition);
						IsMoveToBPosition = true;
					}
					else
					{
						Blackboard -> SetValueAsVector(BB_NextLocation, APosition);
						IsMoveToBPosition = false;
					}
					
					BrainComponent -> RestartLogic();
					return;
				}

				if (!BrainComponent -> IsRunning())
					BrainComponent -> StartLogic();
				return;
			}
				
		case EActionsTypes::EA_BackMovement:
			{
				WasBackMovementBeen = true;
				
				if (IsMoveToBPosition)
				{
					Blackboard -> SetValueAsVector(BB_NextLocation, APosition);
					IsMoveToBPosition = false;
				}
				else
				{
					Blackboard -> SetValueAsVector(BB_NextLocation, BPosition);
					IsMoveToBPosition = true;
				}
				
				BrainComponent -> RestartLogic();
				return;
			}

		case EActionsTypes::EA_Waiting:
			{
				BrainComponent -> StopLogic("");
			}
	}
}
