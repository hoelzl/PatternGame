// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "PGGameMode.generated.h"

UCLASS(minimalapi)
class APGGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APGGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerToWinFactor;

	// Returns power needed to win - needed for the HUD
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

protected:
	// The rate at which the character loses power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	// The power needed to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;

	// The widget class to use for our HUD screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// The instance of the HUD, based on HUDWidgetClass;
	UPROPERTY()
	class UUserWidget* CurrentWidget;
};



