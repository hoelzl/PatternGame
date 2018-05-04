// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "PGGameMode.generated.h"

// Store the current state of gameplay
UENUM(BlueprintType)
enum class EPGPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

/*
 * The game mode (i.e., rules of the game) for the main part of the game.
 */
UCLASS()
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

	UFUNCTION(BlueprintPure, Category = "Victory")
	EPGPlayState GetCurrentGameState() const;

	UFUNCTION(BlueprintCallable, Category = "Victory")
	void SetCurrentGameState(EPGPlayState NewState);

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
	class UUserWidget* HUDWidget;

private:
	// Keeps track of the current play state
	EPGPlayState CurrentGameState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

public:
	void RegisterSpawnVolume(class ASpawnVolume* SpawnVolume);

protected:
	// This will handle any function calls that rely on changing the playing state of the game.
	void HandleNewState(EPGPlayState NewState);
};



