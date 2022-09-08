// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Types.h"
#include "CoreMinimal.h"

#include "CustomMovementComponent.generated.h"

UCLASS(Abstract)
class UCustomMovementComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	virtual ECustomMovementMode GetCustomMovementMode() { return ECustomMovementMode::CMOVE_None; };
	
	virtual void PhysicsProcess(float DeltaTime, int32 Iterations) {};

	virtual bool RotationProcess(float DeltaTime) { return false; };
	
	virtual bool TryOnMovement() { return false; };

	
protected:
	virtual void BeginPlay() override;
	
	TWeakObjectPtr<class UBaseMovementComponent> MovementComponent = nullptr;
	
	TWeakObjectPtr<class ABaseCharacter> Character = nullptr;
};
