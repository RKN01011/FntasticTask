// Copyright Epic Games, Inc. All Rights Reserved.


#include "Animations/Notifications/AnimNotify_Landing.h"

#include "Components/CharacterMeshComponent.h"

void UAnimNotify_Landing::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UCharacterMeshComponent* CharacterMeshComponent = StaticCast<UCharacterMeshComponent*>(MeshComp);
	if (IsValid(CharacterMeshComponent))
	{
		CharacterMeshComponent -> Landing();
	}
}
