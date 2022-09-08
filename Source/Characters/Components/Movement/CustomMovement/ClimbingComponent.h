// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomMovementComponent.h"
#include "Components/LedgeDetector.h"

#include "ClimbingComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARACTERS_API UClimbingComponent : public UCustomMovementComponent
{
	GENERATED_BODY()

public:
	virtual ECustomMovementMode GetCustomMovementMode() override { return ECustomMovementMode::CMOVE_Climbing; };

	virtual void PhysicsProcess(float DeltaTime, int32 Iterations) override;
	
	virtual bool TryOnMovement() override;
	
	void EndMantle() const;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	FClimbingSettings HighMantleSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	FClimbingSettings LowMantleSettings;
	
	FClimbingMovementParameters CurrentMantlingParameters;
	
	ULedgeDetector LDComponent;
	
	FTimerHandle MantlingTimer;
};
