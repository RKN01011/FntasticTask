// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.generated.h"

/* Collision channels */
#define ECC_Climbing ECC_GameTraceChannel1

/* BehaverTree variables names */
const FName BB_NextLocation = FName{"TargetLocation"};

/* Movement */
UENUM(BlueprintType)
enum class ECustomMovementMode : uint8
{
	CMOVE_None,
	CMOVE_Climbing
};

USTRUCT(BlueprintType)
struct FClimbingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0.0f, UIMin = 0.0f))
	float MaxHeight = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0.0f, UIMin = 0.0f))
	float MinHeight = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0.0f, UIMin = 0.0f))
	float MaxHeightStartTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0.0f, UIMin = 0.0f))
	float MinHeightStartTime = .5f;
};

struct FClimbingMovementParameters
{
	FVector InitialLocation = FVector::ZeroVector;
	FRotator InitialRotation = FRotator::ZeroRotator;

	FVector TargetLocation = FVector::ZeroVector;
	FRotator TargetRotation = FRotator::ZeroRotator;

	float Duration = 1.f;
	float StartTime = 0.f;

	class UCurveFloat* MantlingCurve;
};

/* AI */
UENUM(BlueprintType)
enum class EActionsTypes : uint8
{
	EA_Movement,
	EA_BackMovement,
	EA_Waiting
};

USTRUCT(BlueprintType)
struct FMovementInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool NeedSplitMovementByParts = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FirstPartMovementTime = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EActionsTypes FirstPartMovementActions = EActionsTypes::EA_Movement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SecondPartMovementTime = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EActionsTypes SecondPartMovementActions = EActionsTypes::EA_Movement;
};

/* LedgeDetection */
struct FLedgeDetectionInfo
{
	FVector Location = FVector::ZeroVector;

	FVector LedgeNormal = FVector::ZeroVector;

	FRotator Rotation = FRotator::ZeroRotator;
};