// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseAnimInstance.h"

#include "BaseCharacter.h"
#include "Components/Movement/BaseMovementComponent.h"

void UBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	BaseCharacter = StaticCast<ABaseCharacter*>(TryGetPawnOwner());
	checkf(BaseCharacter.IsValid(), TEXT("Character is nullptr in UBaseAnimInstance"));
	
	CharacterMovement = StaticCast<UBaseMovementComponent*>(BaseCharacter -> GetCharacterMovement());
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!CharacterMovement.IsValid())
		return;
	
	Direction = CalculateDirection(CharacterMovement -> Velocity, BaseCharacter -> GetActorRotation());
	Speed = CharacterMovement -> Velocity.Size();

	RightBallEffectorLocation = FVector(-BaseCharacter -> GetLeftBallOffset(), 0.f, 0.f);
	LeftBallEffectorLocation = FVector(BaseCharacter -> GetRightBallOffset(), 0.f, 0.f);
	RootBoneOffset = -FMath::Max(FMath::Abs(RightBallEffectorLocation.X), FMath::Abs(LeftBallEffectorLocation.X));

	MovementMode = CharacterMovement -> MovementMode;
	CustomMovementMode = (ECustomMovementMode)CharacterMovement -> CustomMovementMode;
	PreviousCustomMovementMode = (ECustomMovementMode)CharacterMovement -> PreviousCustomMovementMode;
}
