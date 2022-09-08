// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterMeshComponent.h"
#include "Components/Movement/BaseMovementComponent.h"
#include "Components/Movement/CustomMovement/CustomMovementComponent.h"

const float Interp_Speed = 20.0f;

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(
		ObjectInitializer
			.SetDefaultSubobjectClass<UBaseMovementComponent>(CharacterMovementComponentName)
	)
{
	MovementComponent = StaticCast<UBaseMovementComponent*>(GetCharacterMovement());
	
	USkeletalMeshComponent* MeshComponent = GetMesh();
	MeshComponent -> CastShadow = true;
	MeshComponent -> bCastDynamicShadow = true;
	
	IKScale = GetActorScale3D().Z;
	IKDistance = GetCapsuleComponent() -> GetScaledCapsuleHalfHeight() * IKScale + 60.0f;
}

void ABaseCharacter::Climb()
{
	MovementComponent -> TrySwitchMovementModeTo(ECustomMovementMode::CMOVE_Climbing);
}

float ABaseCharacter::GetLeftBallOffset() const
{
	return FMath::Abs<float>(LeftBallOffset);
}

float ABaseCharacter::GetRightBallOffset() const
{
	return FMath::Abs<float>(RightBallOffset);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterMeshComponent* CharacterMeshComponent = StaticCast<UCharacterMeshComponent*>(GetMesh());
	CharacterMeshComponent -> OnLanded.BindUObject(this, &ABaseCharacter::LandedHandler);
	InitCustomMovement();
}

void ABaseCharacter::InitCustomMovement()
{
	TArray<UCustomMovementComponent*> Components;
	GetComponents<UCustomMovementComponent>(Components, false);
	MovementComponent -> SetCustomMovementComponents(Components);
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	MovementComponent -> DisableMovement();
}

float ABaseCharacter::GetIKOffsetForASocket(const FName& SocketName, float Offset, float DeltaTime) const
{
	FVector const SocketLocation = GetMesh() -> GetSocketLocation(SocketName);
	FVector const TraceStart(SocketLocation.X, SocketLocation.Y, GetActorLocation().Z + 5.f);
	FVector const TraceEnd = TraceStart - IKDistance * FVector::UpVector;
	
	FHitResult HitResult;
	const FCollisionShape CollisionShape = FCollisionShape::MakeBox(FVector(10.f, 5.f, 5.f));
	const FQuat CollisionShapeRotation = GetActorRotation().Quaternion();
	if (GetWorld() -> SweepSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionShapeRotation,
		ECC_Visibility, CollisionShape))
	{
		const float TargetOffset = (TraceEnd.Z - HitResult.Location.Z) / IKScale + 60.0f;
		return FMath::FInterpTo(Offset, TargetOffset, DeltaTime, Interp_Speed);
	}
		
	return 0.f;
}

void ABaseCharacter::LandedHandler()
{
	MovementComponent -> SetDefaultMovementMode();
}