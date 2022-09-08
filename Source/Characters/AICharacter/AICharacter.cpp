// Copyright Epic Games, Inc. All Rights Reserved.


#include "AICharacter.h"

#include "AIController.h"
#include "Controller/AICharacterController.h"
#include "Kismet/GameplayStatics.h"


void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(SpawnSound))
		return;

	PlaySpawnSound();
	ExecuteEffect();
}

void AAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ExecuteEffect();
	
	Super::EndPlay(EndPlayReason);
}

void AAICharacter::InitControlling(FVector TargetPosition, UBehaviorTree* NewBehaviorTree)
{
	AAICharacterController* CharacterController = StaticCast<AAICharacterController*>(GetController());
	CharacterController -> InitControlling(TargetPosition, NewBehaviorTree);
}


void AAICharacter::PlaySpawnSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawnSound, GetActorLocation(), GetActorRotation());
}

void AAICharacter::PlayFinishReachedSound()
{
	if (!IsValid(FinishReachedSound))
		return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FinishReachedSound, GetActorLocation(), GetActorRotation());
}

void AAICharacter::ExecuteEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionVFX, GetActorLocation());
}

UBehaviorTree* AAICharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}

FVector AAICharacter::GetTargetPositionToMove()
{
	return GetActorTransform().TransformPosition(TargetPositionToMove);
}

FMovementInfo AAICharacter::GetMovementInfo()
{
	return MovementInfo;
}