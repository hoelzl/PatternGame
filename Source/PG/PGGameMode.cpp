// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PG.h"
#include "PGGameMode.h"
#include "PGCharacter.h"

APGGameMode::APGGameMode()
{
#if 0
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
#endif	
	// set default pawn class to our character
	DefaultPawnClass = APGCharacter::StaticClass();
}
