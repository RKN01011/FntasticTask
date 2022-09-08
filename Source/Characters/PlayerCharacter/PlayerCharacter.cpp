// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"


#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/Movement/BaseMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Environment/interface/Interactable.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseControllerRotationPitch = bUseControllerRotationYaw = bUseControllerRotationRoll = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent -> SetupAttachment(RootComponent);
	SpringArmComponent -> bUsePawnControlRotation = true;
	SpringArmComponent -> bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent -> SetupAttachment(SpringArmComponent);
	CameraComponent -> bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent -> BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent -> BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent -> BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	InputComponent -> BindAxis("Turn", this, &APlayerCharacter::Turn);
	
	InputComponent -> BindAction("Climb", IE_Pressed, this, &APlayerCharacter::Climb);
	InputComponent -> BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	
	InputComponent -> BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TraceLineOfSight();
}

void APlayerCharacter::TraceLineOfSight()
{
	FVector ViewLocation;
	FRotator ViewRotator;

	APlayerController* PlayerController = GetController<APlayerController>();
	PlayerController -> GetPlayerViewPoint(ViewLocation, ViewRotator);

	FVector ViewDirection = ViewRotator.Vector();
	FVector TraceEnd = ViewLocation + ViewDirection * LineOfSightDistance;

	FHitResult HitResult;
	if (!GetWorld() -> LineTraceSingleByChannel(HitResult, ViewLocation, TraceEnd, ECC_Visibility))
	{
		return;
	}

	if (LineOfSightObject.GetObject() != HitResult.Actor)
	{
		LineOfSightObject = HitResult.Actor.Get();
	}
}

void APlayerCharacter::Interact()
{
	if (LineOfSightObject.GetInterface())
	{
		LineOfSightObject -> Interact();
	}
}

float APlayerCharacter::GetAngleCameraToCharacter() const
{
	const FVector ToCharacter = CameraComponent -> GetComponentRotation().Vector().GetSafeNormal2D();
	const float ForwardCosAngle = FVector::DotProduct(GetActorForwardVector(), ToCharacter);
	const float DirectionModifer = FVector::DotProduct(GetActorRightVector(), ToCharacter) < 0 ? -1.f : 1.f;

	return FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle)) * DirectionModifer;
}

FPlayerCameraRotationInfo APlayerCharacter::CalculatingAngleRotationAimingAndHead(float DeltaTime,
	FPlayerCameraRotationInfo CurrentInfo)
{
	FPlayerCameraRotationInfo PlayerCameraRotationInfo;
	
	const float AngleFull = GetAngleCameraToCharacter();
    const float CurrentHeadAngle = FMath::Abs(AngleFull) > 80.f ? 0.f : FMath::Clamp(AngleFull, -60.f, 60.f);

    PlayerCameraRotationInfo.HeadRotationYawAngle = FMath::FInterpTo(CurrentInfo.HeadRotationYawAngle,
    	CurrentHeadAngle, DeltaTime, 3.f);
    
    const FVector AimDirectionWorld = GetBaseAimRotation().Vector();
    const FVector AimDirectionLocal = GetTransform().InverseTransformVectorNoScale(AimDirectionWorld);
    FRotator AimRotation = AimDirectionLocal.ToOrientationRotator();
    AimRotation.Yaw = AngleFull;
	PlayerCameraRotationInfo.AimRotation = AimRotation;

	return PlayerCameraRotationInfo;
}

USpringArmComponent* APlayerCharacter::GetSpringArmComponent() const
{
	return SpringArmComponent;
}

void APlayerCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator const YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		AddMovementInput(YawRotator.RotateVector(FVector::ForwardVector), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		FRotator const YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		AddMovementInput(YawRotator.RotateVector(FVector::RightVector), Value);
	}
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerCharacter::Jump()
{
	if (!MovementComponent -> IsMovementMod(MOVE_Walking))
		return;
	
	Super::Jump();
}
