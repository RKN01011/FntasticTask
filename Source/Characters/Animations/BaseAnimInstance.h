// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Types.h"
#include "Animation/AnimInstance.h"

#include "BaseAnimInstance.generated.h"

UCLASS()
class CHARACTERS_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables | BaseMovement")
	float Direction = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables | BaseMovement")
	float Speed = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables | MovementModes")
	TEnumAsByte<EMovementMode> MovementMode = MOVE_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables | MovementModes")
	ECustomMovementMode CustomMovementMode = ECustomMovementMode::CMOVE_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables | MovementModes")
	ECustomMovementMode PreviousCustomMovementMode = ECustomMovementMode::CMOVE_None;
	
	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category="Variables | IKSettings")
	FVector LeftBallEffectorLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category="Variables | IKSettings")
	FVector RightBallEffectorLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category="Variables | IKSettings")
	float RootBoneOffset = 0.f;

	TWeakObjectPtr<class UBaseMovementComponent> CharacterMovement;
	
	TWeakObjectPtr<class ABaseCharacter> BaseCharacter;
};
