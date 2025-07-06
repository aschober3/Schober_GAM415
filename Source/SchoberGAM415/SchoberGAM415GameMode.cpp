// Copyright Epic Games, Inc. All Rights Reserved.

#include "SchoberGAM415GameMode.h"
#include "SchoberGAM415Character.h"
#include "UObject/ConstructorHelpers.h"

ASchoberGAM415GameMode::ASchoberGAM415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
