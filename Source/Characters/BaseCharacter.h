// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseCharacter.generated.h"

UCLASS(Abstract, NotBlueprintable)
class CHARACTERS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

	virtual void Landed(const FHitResult& Hit) override;
	
	virtual void MoveForward(float Value) {};
	
	virtual void MoveRight(float Value) {};
	
	virtual void Turn(float Value) {};
	
	virtual void LookUp(float Value) {};

	UFUNCTION(BlueprintCallable)
	virtual void Climb();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetLeftBallOffset() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRightBallOffset() const;

protected:
	virtual void BeginPlay() override;

	float GetIKOffsetForASocket(const FName& SocketName, float Offset, float DeltaTime) const;

	void InitCustomMovement();

	void LandedHandler();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="IK settings")
	FName LeftBallName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="IK settings")
	FName RightBallName;
	
	TWeakObjectPtr<class UBaseMovementComponent> MovementComponent = nullptr;

	float LeftBallOffset = 0.0f;
	
	float RightBallOffset = 0.0f;
	
	float IKDistance = 0.0f;
	
	float IKScale = 0.0f;
};


