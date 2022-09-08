// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomMovementComponent.h"

#include "BaseCharacter.h"
#include "Components/Movement/BaseMovementComponent.h"

void UCustomMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = StaticCast<ABaseCharacter*>(GetOwner());
	MovementComponent = StaticCast<UBaseMovementComponent*>(Character -> GetMovementComponent());
}
