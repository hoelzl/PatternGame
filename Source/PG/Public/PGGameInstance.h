// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Engine/GameInstance.h"
#include "Characters/PGCharacter.h"
#include "PGGameInstance.generated.h"

/**
 * The game instance for the pattern game.
 * In UE4 game instances are "singletons" that persist throughout the game, even
 * when the level changes. The main purpose of this game instance class is to store
 * the class of the character the player has selected in the startup level.
 */
UCLASS()
class PG_API UPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Selection")
	TSubclassOf<APGCharacter> PlayerCharacterClass;
	
};
