// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"

#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

USTRUCT(BlueprintType)
struct FPlayerCameraRotationInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float HeadRotationYawAngle = 0.f;

	UPROPERTY(BlueprintReadOnly)
	FRotator AimRotation = FRotator::ZeroRotator;
};

UCLASS(Blueprintable)
class CHARACTERS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void MoveForward(float Value) override;
	
	virtual void MoveRight(float Value) override;
	
	virtual void LookUp(float Value) override;
	
	virtual void Turn(float Value) override;
	
	virtual void Jump() override;

	void Interact();

	float GetAngleCameraToCharacter() const;
	
	UFUNCTION(BlueprintCallable)
	FPlayerCameraRotationInfo CalculatingAngleRotationAimingAndHead(float DeltaTime,
		FPlayerCameraRotationInfo CurrentInfo);
	
	void TraceLineOfSight();
	
	USpringArmComponent* GetSpringArmComponent() const;
	
	UPROPERTY()
	TScriptInterface<class IInteractable> LineOfSightObject;

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components | Camera")
	UCameraComponent* CameraComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components | Camera")
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interact | Interactive")
	float LineOfSightDistance = 1000.f;
};
