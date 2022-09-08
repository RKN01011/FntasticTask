// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class CHARACTERS_API IInteractable
{
	GENERATED_BODY()
	
public:
	virtual void Interact() PURE_VIRTUAL(IInteractable::Interact, );
};
