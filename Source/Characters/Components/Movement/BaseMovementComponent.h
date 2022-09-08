// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Types.h"
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BaseMovementComponent.generated.h"

class UCustomMovementComponent;

UCLASS()
class CHARACTERS_API UBaseMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UBaseMovementComponent();

	void SetCustomMovementComponents(const TArray<UCustomMovementComponent*>& Components);

	bool TrySwitchMovementModeTo(ECustomMovementMode Mode);
	
	bool IsMovementMod(EMovementMode Mode) const;
	bool IsMovementMod(ECustomMovementMode Mode) const;

	uint8 PreviousCustomMovementMode;
	

protected:
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	virtual void PhysCustom(float DeltaTime, int32 Iterations) override;

	virtual void PhysicsRotation(float DeltaTime) override;
	
	TArray<UCustomMovementComponent*> CustomMovementComponents;
	
	TWeakObjectPtr<UCustomMovementComponent> CustomMovementComponent;
};

