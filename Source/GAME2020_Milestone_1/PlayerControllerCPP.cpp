// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerCPP.h"
#include "PlayerCameraManagerCPP.h"

APlayerControllerCPP::APlayerControllerCPP()
{
	PlayerCameraManagerClass = APlayerCameraManagerCPP::StaticClass();
}
