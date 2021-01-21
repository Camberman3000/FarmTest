// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmingTestGameMode.h"
#include "FarmingTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFarmingTestGameMode::AFarmingTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
