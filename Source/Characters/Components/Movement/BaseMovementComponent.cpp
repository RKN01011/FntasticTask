// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseMovementComponent.h"

#include "CustomMovement/CustomMovementComponent.h"


UBaseMovementComponent::UBaseMovementComponent()
{
	bOrientRotationToMovement = 1;
	RotationRate = FRotator(0.0f, 540.0f, 0.0f);
}

void UBaseMovementComponent::SetCustomMovementComponents(const TArray<UCustomMovementComponent*>& Components)
{
	CustomMovementComponents = Components;
}

bool UBaseMovementComponent::TrySwitchMovementModeTo(ECustomMovementMode Mode)
{
	for (const auto Component : CustomMovementComponents)
		if (Component -> GetCustomMovementMode() == Mode)
			return Component -> TryOnMovement();
	return false;
}

bool UBaseMovementComponent::IsMovementMod(EMovementMode Mode) const
{
	return MovementMode == Mode;
}

bool UBaseMovementComponent::IsMovementMod(ECustomMovementMode Mode) const
{
	return CustomMovementMode == (uint8)Mode;
}

void UBaseMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
	
	PreviousCustomMovementMode = PreviousCustomMode;
	
	if (PreviousMovementMode == MOVE_Custom && CustomMovementComponent.IsValid())
		CustomMovementComponent = nullptr;
	
	if (MovementMode == MOVE_Custom)
		for (const auto Component : CustomMovementComponents)
			if (Component -> GetCustomMovementMode() == (ECustomMovementMode)CustomMovementMode)
				CustomMovementComponent = Component;
}

void UBaseMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
	Super::PhysCustom(DeltaTime, Iterations);
	
	CustomMovementComponent -> PhysicsProcess(DeltaTime, Iterations);
}

void UBaseMovementComponent::PhysicsRotation(float DeltaTime)
{
	if (IsMovementMod(ECustomMovementMode::CMOVE_Climbing) && !CustomMovementComponent -> RotationProcess(DeltaTime))
		return;
	
	Super::PhysicsRotation(DeltaTime);
}
