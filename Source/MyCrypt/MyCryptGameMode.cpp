// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCryptGameMode.h"
#include "MyCryptCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyCryptGameMode::AMyCryptGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
