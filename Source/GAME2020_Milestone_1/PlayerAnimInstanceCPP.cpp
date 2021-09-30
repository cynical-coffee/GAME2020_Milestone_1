// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstanceCPP.h"
#include "PlayerCharacterCPP.h"

void UPlayerAnimInstanceCPP::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningPawn == nullptr)
	{
		OwningPawn = TryGetPawnOwner();
		if (OwningPawn)
		{
			PlayerCharacter = Cast<APlayerCharacterCPP>(OwningPawn);
		}
	}
}

void UPlayerAnimInstanceCPP::UpdateAnimationProperties(float deltaTime)
{
	if (OwningPawn == nullptr)
	{
		OwningPawn = TryGetPawnOwner();
	}
}
