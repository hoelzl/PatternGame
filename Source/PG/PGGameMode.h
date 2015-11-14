// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "PGGameMode.generated.h"

UCLASS(minimalapi)
class APGGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APGGameMode();

	virtual void Tick(float DeltaTime) override;

protected:
	// The rate at which the character loses power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	float DecayRate;
};



