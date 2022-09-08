// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICharacter/AICharacter.h"
#include "AICharacterController.generated.h"

UCLASS()
class CHARACTERS_API AAICharacterController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void InitControlling(FVector TargetPosition, UBehaviorTree* BehaviorTree);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float TargetReachRadius = 100.f;
	
	FVector APosition;
	
	FVector BPosition;
	
	TWeakObjectPtr<class AAICharacter> Character = nullptr;
	
	bool IsMoveToBPosition = true;
	
	bool WasBackMovementBeen = false;
	
	FTimerHandle FirstPartMovementTimer;
	
	FTimerHandle SecondPartMovementTimer;

	void FirstPartMovement();
	
	void DoActions(EActionsTypes ActionsTypes);

	void SecondPartMovement();
};
