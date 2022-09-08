// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interface/Interactable.h"
#include "SpawnButton.generated.h"

UCLASS()
class CHARACTERS_API ASpawnButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	virtual void Interact() override;

	UFUNCTION(BlueprintImplementableEvent)
	void InteractButton();
};
