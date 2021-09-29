// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterCPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacterCPP::APlayerCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	// Spring Arm
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	ThirdPersonSpringArm->SetupAttachment(RootComponent);
	ThirdPersonSpringArm->bUsePawnControlRotation = true;
	const FVector ThirdPersonSpringLocation(0.0, 0.0, 70.0);
	ThirdPersonSpringArm->SetRelativeLocation(ThirdPersonSpringLocation);
	const FVector ThirdPersonSpringOffset(0.0, 0.0, 100.0);
	ThirdPersonSpringArm->SocketOffset = ThirdPersonSpringOffset;
	ThirdPersonSpringArm->bEnableCameraRotationLag = true;

	// Third-Person Camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	const FRotator CameraRotation(-30.0, 0.0, 0.0);
	ThirdPersonCamera->SetRelativeRotation(CameraRotation);
}

// Called when the game starts or when spawned
void APlayerCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacterCPP::MoveForward(float value)
{
	FVector forward = GetActorForwardVector();
	AddMovementInput(forward, value);
}

void APlayerCharacterCPP::MoveRight(float value)
{
	FVector right = GetActorRightVector();
	AddMovementInput(right, value);
}

// Called every frame
void APlayerCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterCPP::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterCPP::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterCPP::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterCPP::AddControllerPitchInput);
}

