// Copyright Epic Games, Inc. All Rights Reserved.

#include "BPvCPPGameMode.h"
#include "BPvCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABPvCPPGameMode::ABPvCPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
