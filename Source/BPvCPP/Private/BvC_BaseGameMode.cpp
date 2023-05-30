// Copyright Epic Games, Inc. All Rights Reserved.

#include "BvC_BaseGameMode.h"
#include "BvC_Character.h"
#include "UObject/ConstructorHelpers.h"

ABvC_BaseGameMode::ABvC_BaseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
