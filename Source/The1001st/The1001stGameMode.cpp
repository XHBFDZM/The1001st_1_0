// Copyright Epic Games, Inc. All Rights Reserved.

#include "The1001stGameMode.h"
#include "The1001st/Public/Character/The1001stCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThe1001stGameMode::AThe1001stGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
