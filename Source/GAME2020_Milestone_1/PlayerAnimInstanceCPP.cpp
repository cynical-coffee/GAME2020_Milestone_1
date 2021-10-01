// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstanceCPP.h"
#include "PlayerCharacterCPP.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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

	if (OwningPawn)
	{
		// Movement
		FVector  vSpeed = OwningPawn->GetVelocity();
		FVector vLateralSpeed = FVector(vSpeed.X, vSpeed.Y, 0);
		fMovementSpeed = vLateralSpeed.Size();
		fDirection = CalculateDirection(vSpeed, OwningPawn->GetControlRotation());
		bIsInAir = OwningPawn->GetMovementComponent()->IsFalling();

		if (PlayerCharacter == nullptr)
		{
			PlayerCharacter = Cast<APlayerCharacterCPP>(OwningPawn);
		}

		if (PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}
	}
}
