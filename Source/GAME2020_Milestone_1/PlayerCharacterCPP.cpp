// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterCPP.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	const FVector ThirdPersonSpringLocation(0.0, 0.0, 50.0);
	ThirdPersonSpringArm->SetRelativeLocation(ThirdPersonSpringLocation);
	const FVector ThirdPersonSpringOffset(0.0, 0.0, 300.0);
	ThirdPersonSpringArm->TargetArmLength = 600.f;
	ThirdPersonSpringArm->SocketOffset = ThirdPersonSpringOffset;
	ThirdPersonSpringArm->bEnableCameraRotationLag = true;

	// Third-Person Camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	const FRotator CameraRotation(-30.0, 0.0, 0.0);
	ThirdPersonCamera->SetRelativeRotation(CameraRotation);

	// Player movement values
	GetCharacterMovement()->GravityScale = 3.0f;
	GetCharacterMovement()->JumpZVelocity = 1400.0f;
}

// Called when the game starts or when spawned
void APlayerCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacterCPP::MoveForward(float value)
{
	/*FVector forward = GetActorForwardVector();
	AddMovementInput(forward, value);*/

	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator rRotation = Controller->GetControlRotation();
		const FRotator rYawRotation(0.0, rRotation.Yaw, 0);

		const FVector vDirection = FRotationMatrix(rYawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(vDirection, value);
	}
}

void APlayerCharacterCPP::MoveRight(float value)
{
	/*FVector right = GetActorRightVector();
	AddMovementInput(right, value);*/

	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator rRotation = Controller->GetControlRotation();
		const FRotator rYawRotation(0.0, rRotation.Yaw, 0);

		const FVector vDirection = FRotationMatrix(rYawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(vDirection, value);
	}
}

void APlayerCharacterCPP::LaunchJump()
{
	JumpMaxCount = 2;
	const float vel = GetVelocity().Z;
	const FVector launchVel(0.0, 0.0, -800.0);
	if (vel >= 0.0f)
	{
		LaunchCharacter(launchVel, false, false);
	}
}

void APlayerCharacterCPP::DoubleJump()
{
	JumpMaxCount = 2;
	const FVector launchVel(0.0, 0.0, -800.0);
	if (GetCharacterMovement()->IsFalling())
	{
		if (JumpCurrentCount <= JumpMaxCount)
		{
			LaunchCharacter(launchVel, false, false);
		}
		
	}
}

void APlayerCharacterCPP::ForwardTrace()
{
	FHitResult outHit;
	FVector start = GetActorLocation();
	FVector end = (GetActorForwardVector() * 150.0f) + GetActorLocation();
	FCollisionQueryParams collisionQuery;
	//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1, 0, 1);
	if (GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionQuery))
	{
		if (outHit.bBlockingHit)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *outHit.GetActor()->GetName()));
			}
		}
	}

	outHitNormal = outHit.Normal;
	wallLocation = outHit.Location;
}

void APlayerCharacterCPP::HeightTrace()
{
	FHitResult outHit;
	FVector start = GetActorLocation() + FVector(0, 0, 500.0f);
	FVector end = (GetActorForwardVector() * 75.0f) + start - FVector(0, 0, 500.0f);
	FCollisionQueryParams collisionQuery;
	//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1, 0, 1);
	if (GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionQuery))
	{
		if (outHit.bBlockingHit)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("You are hitting: %s"), *outHit.GetActor()->GetName()));
			}
		}
	}

}

// Called every frame
void APlayerCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForwardTrace();
	HeightTrace();
}

// Called to bind functionality to input
void APlayerCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterCPP::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterCPP::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterCPP::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterCPP::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacterCPP::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacterCPP::DoubleJump);
}

