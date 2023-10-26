// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PGGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Characters/RobotCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PG.h"
#include "PGGameInstance.h"
#include "PGPlayerController.h"
#include "Utilities/SpawnVolume.h"

APGGameMode::APGGameMode() : PowerToWinFactor{2.f}, DecayRate{0.05f}, CurrentGameState{EPGPlayState::EUnknown}
{

	const UWorld* World = GetWorld();
	UGameInstance* GameInstance = (World != nullptr) ? World->GetGameInstance() : nullptr;
	const UPGGameInstance* PGGameInstance = Cast<UPGGameInstance>(GameInstance);

	if (PGGameInstance && PGGameInstance->PlayerCharacterClass)
	{
		DefaultPawnClass = PGGameInstance->PlayerCharacterClass;
	}
	else
	{
		DefaultPawnClass = ARobotCharacter::StaticClass();
	}
	check(DefaultPawnClass);

	PlayerControllerClass = APGPlayerController::StaticClass();

	static auto HUDBlueprintClassName = TEXT("WidgetBlueprint'/Game/Blueprints/BatteryHUD.BatteryHUD_C'");
	static auto HUDFinder = ConstructorHelpers::FClassFinder<UUserWidget>(HUDBlueprintClassName);
	if (HUDFinder.Succeeded())
	{
		HUDWidgetClass = HUDFinder.Class;
	}
}

void APGGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentGameState(EPGPlayState::EPlaying);

	// Set up victory conditions
	if (const APGCharacter* PlayerCharacter = Cast<APGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		PowerToWin = PowerToWinFactor * PlayerCharacter->GetInitialPower();
	}

	// Set up the HUD
	if (HUDWidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget != nullptr)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void APGGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APGCharacter* MyCharacter = Cast<APGCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentGameState(EPGPlayState::EWon);
		}
		else if (MyCharacter->GetCurrentPower() > 0)
		{
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * MyCharacter->GetInitialPower());
		}
		else
		{
			SetCurrentGameState(EPGPlayState::EGameOver);
		}
	}
}

float APGGameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EPGPlayState APGGameMode::GetCurrentGameState() const
{
	return CurrentGameState;
}

void APGGameMode::SetCurrentGameState(EPGPlayState NewState)
{
	CurrentGameState = NewState;
	HandleNewState(NewState);
}

void APGGameMode::RegisterSpawnVolume(class ASpawnVolume* SpawnVolume)
{
	SpawnVolumeActors.AddUnique(SpawnVolume);
	HandleNewState(CurrentGameState);
}

void APGGameMode::HandleNewState(EPGPlayState NewState)
{
	switch (NewState)
	{
	case EPGPlayState::EPlaying:
	{
		// Spawn volumes active
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(true);
		}
	}
	break;
	case EPGPlayState::EWon:
	{
		// Spawn volumes inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
	}
	break;
	case EPGPlayState::EGameOver:
	{
		// Spawn volumes inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
		// Block user input
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
		{
			PlayerController->SetCinematicMode(true, false, false, true, false);
		}
		// Ragdoll the character
		if (const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
		{
			PlayerCharacter->GetMesh()->SetSimulatePhysics(true);
			PlayerCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;
	case EPGPlayState::EUnknown:
	default:
	{
		// Do nothing
	}
	break;
	}
}
