// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterCPP.generated.h"

UCLASS()
class GAME2020_MILESTONE_1_API APlayerCharacterCPP : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
		class USpringArmComponent* ThirdPersonSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "True"))
		class UCameraComponent* ThirdPersonCamera;

	FVector outHitNormal;
	FVector wallLocation;

public:
	// Sets default values for this character's properties
	APlayerCharacterCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float value);
	void MoveRight(float value);
	void LaunchJump();
	void DoubleJump();
	void Attack();
	void ForwardTrace();
	void HeightTrace();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int GetMaxJumpCount();
	int GetJumpCount();

};
