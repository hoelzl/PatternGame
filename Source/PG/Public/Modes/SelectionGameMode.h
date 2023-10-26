// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Characters/PGCharacter.h"
#include "GameFramework/GameMode.h"
#include "SelectionGameMode.generated.h"

/**
 * The game mode (i.e., rules) for the initial selection of a player character.
 */
UCLASS()
class PG_API ASelectionGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASelectionGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "CharacterSelection")
	void SelectCharacter(APGCharacter* Character);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	FName NextLevelName;

protected:
	// The widget class to use for our HUD screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// The instance of the HUD, based on HUDWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	class UUserWidget* HUDWidget;
};
