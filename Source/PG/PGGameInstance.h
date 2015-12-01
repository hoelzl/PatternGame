// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Engine/GameInstance.h"
#include "PGCharacter.h"
#include "PGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PG_API UPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Selection")
	TSubclassOf<APGCharacter> PlayerCharacterClass;
	
};
