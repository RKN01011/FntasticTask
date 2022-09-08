// Copyright Epic Games, Inc. All Rights Reserved.

#include "Components/CharacterMeshComponent.h"

void UCharacterMeshComponent::Landing()
{
	OnLanded.ExecuteIfBound();
}
