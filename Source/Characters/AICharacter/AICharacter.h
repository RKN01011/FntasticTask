// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Types.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

#include "AICharacter.generated.h"

UCLASS(Blueprintable)
class CHARACTERS_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	void PlaySpawnSound();
	
	void PlayFinishReachedSound();
	
	void ExecuteEffect();
	
	UBehaviorTree* GetBehaviorTree() const;

	FVector GetTargetPositionToMove();

	FMovementInfo GetMovementInfo();

	UFUNCTION(BlueprintCallable)
	void InitControlling(FVector TargetPosition, UBehaviorTree* NewBehaviorTree);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings | Logic")
	UBehaviorTree* BehaviorTree = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings | Sounds")
	USoundBase* SpawnSound = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings | Sounds")
	USoundBase* FinishReachedSound = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings | Effects")
	UParticleSystem* ExplosionVFX = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(MakeEditWidget), Category="Settings | Movement")
	FVector TargetPositionToMove;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings | Movement")
	FMovementInfo MovementInfo;
};
