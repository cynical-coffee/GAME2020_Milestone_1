// Copyright Epic Games, Inc. All Rights Reserved.


#include "GAME2020_Milestone_1GameModeBase.h"
#include "PlayerCharacterCPP.h"
#include "PlayerControllerCPP.h"

AGAME2020_Milestone_1GameModeBase::AGAME2020_Milestone_1GameModeBase()
{
	DefaultPawnClass = APlayerCharacterCPP::StaticClass();
	PlayerControllerClass = APlayerControllerCPP::StaticClass();
}
