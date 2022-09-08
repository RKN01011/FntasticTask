// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMeshComponent.generated.h"

DECLARE_DELEGATE(FLanded)

/**
 * 
 */
UCLASS()
class CHARACTERS_API UCharacterMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	FLanded OnLanded;
	
	void Landing();
};
