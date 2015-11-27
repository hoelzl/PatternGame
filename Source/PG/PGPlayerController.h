// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "GameFramework/PlayerController.h"
#include "PGPlayerController.generated.h"

/**
 * Player controller for the pattern game.
 */
UCLASS()
class PG_API APGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APGPlayerController();

protected:
	UPROPERTY()
	class APGCharacter* PGCharacter;

	virtual void Possess(APawn* Pawn) override;
	virtual void SetupInputComponent() override;

	void Jump();
	void StopJumping();
	void CollectPickups();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void AddControllerYawInput(float Value);
	void TurnAtRate(float Rate);
	void AddControllerPitchInput(float Value);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
};

