// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClimbingComponent.h"

#include "BaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/Movement/BaseMovementComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Character.h"

constexpr float ANIM_MONTAGE_RATE = 1.0f;

void UClimbingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LDComponent.Init(GetWorld(), Character.Get(), Character -> GetCapsuleComponent());
}

bool UClimbingComponent::TryOnMovement()
{
	FLedgeDetectionInfo LedgeDetection;
	if (!MovementComponent -> IsMovementMod(MOVE_Falling) && LDComponent.DetectLedge(LedgeDetection))
	{
		const FVector CharacterLocation = Character -> GetActorLocation();
		const float Height = (LedgeDetection.Location - CharacterLocation).Z;

		const FClimbingSettings Settings = Height <= LowMantleSettings.MaxHeight ?
			LowMantleSettings : HighMantleSettings;
		
		float MinRange, MaxRange;
		Settings.Curve -> GetTimeRange(MinRange, MaxRange);
		
		const FVector2D DistanceRange(Settings.MinHeight, Settings.MaxHeight);
		const FVector2D TimeRange(Settings.MinHeightStartTime, Settings.MaxHeightStartTime);
		UAnimInstance* AnimInstance = Character -> GetMesh() -> GetAnimInstance();
			
		CurrentMantlingParameters.MantlingCurve = Settings.Curve;
		CurrentMantlingParameters.InitialLocation = CharacterLocation;
		CurrentMantlingParameters.InitialRotation = Character -> GetActorRotation();
		CurrentMantlingParameters.TargetLocation = LedgeDetection.Location;
		CurrentMantlingParameters.TargetRotation = LedgeDetection.Rotation;
		CurrentMantlingParameters.Duration = MaxRange - MinRange;
		CurrentMantlingParameters.StartTime = FMath::GetMappedRangeValueClamped(DistanceRange, TimeRange, Height);
		
		MovementComponent -> SetMovementMode(MOVE_Custom, (uint8)GetCustomMovementMode());
		AnimInstance -> Montage_Play(Settings.Montage, ANIM_MONTAGE_RATE,
			EMontagePlayReturnType::Duration, CurrentMantlingParameters.StartTime);
		GetWorld() -> GetTimerManager().SetTimer(MantlingTimer, this, &UClimbingComponent::EndMantle,
			CurrentMantlingParameters.Duration, false);

		return true;
	}

	return false;
}

void UClimbingComponent::PhysicsProcess(float DeltaTime, int32 Iterations)
{
	FHitResult Hit;
	
	const float ElapsedTime = GetWorld() ->
		GetTimerManager().GetTimerElapsed(MantlingTimer) + CurrentMantlingParameters.StartTime;
	const float PositionAlpha = CurrentMantlingParameters.MantlingCurve -> GetFloatValue(ElapsedTime);
	
	const FVector NewLocation = FMath::Lerp(CurrentMantlingParameters.InitialLocation,
		CurrentMantlingParameters.TargetLocation, PositionAlpha);
	const FRotator NewRotation = FMath::Lerp(CurrentMantlingParameters.InitialRotation,
		CurrentMantlingParameters.TargetRotation, PositionAlpha);

	const FVector Delta = NewLocation - Character -> GetActorLocation();
	
	MovementComponent -> Velocity = Delta / DeltaTime;
	MovementComponent -> SafeMoveUpdatedComponent(Delta, NewRotation, false, Hit);
}

void UClimbingComponent::EndMantle() const
{
	MovementComponent -> SetDefaultMovementMode();
}
