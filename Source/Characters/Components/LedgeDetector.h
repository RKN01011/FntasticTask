// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Types.h"

class UCapsuleComponent;

class ULedgeDetector
{
public:
	void Init(UWorld* CurrentWorld, ACharacter* Owner, UCapsuleComponent* Capsule);

	bool DetectLedge(FLedgeDetectionInfo& LedgeDetection);
	
protected:
	bool HasClimbForward();

	bool HasClimbTop();

	bool HasCharacterFit();
	
	TWeakObjectPtr<UWorld> World = nullptr;

	TWeakObjectPtr<ACharacter> Character = nullptr;

	TWeakObjectPtr<UCapsuleComponent> CapsuleComponent = nullptr;
	
	float MinLedgeHeight = 40.f;

	float MaxLedgeHeight = 200.f;

	float ForwardCheckDistance = 100.f;

	FCollisionQueryParams QueryParams;

	FHitResult ForwardCheckHitResult;

	FHitResult DownwardCheckHitResult;
	
	FVector CharacterBottom;

	const float DrawTime = 2.0f;
};
