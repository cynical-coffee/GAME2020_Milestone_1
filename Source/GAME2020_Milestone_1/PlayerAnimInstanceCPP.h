// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstanceCPP.generated.h"

/**
 * 
 */
UCLASS()
class GAME2020_MILESTONE_1_API UPlayerAnimInstanceCPP : public UAnimInstance
{
	GENERATED_BODY()

	// Animation Properties
	virtual void NativeInitializeAnimation() override;
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
		void UpdateAnimationProperties(float deltaTime);

public:

	// Character Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class APawn* OwningPawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class APlayerCharacterCPP* PlayerCharacter;

	// Movement Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement);
	float fMovementSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement);
	float fDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement);
	bool bIsAccelerating;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;
};
