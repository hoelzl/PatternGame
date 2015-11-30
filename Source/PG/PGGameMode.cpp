// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "PGGameMode.h"
#include "PGPlayerController.h"
#include "RobotCharacter.h"
#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

APGGameMode::APGGameMode() :
    PowerToWinFactor{ 2.f },
	DecayRate{ 0.05f },
	CurrentGameState{ EPGPlayState::EUnknown }
{
	// set default pawn class for our character
	DefaultPawnClass = ARobotCharacter::StaticClass();
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


	// Find all spawn volumes
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentGameState(EPGPlayState::EPlaying);

	// Set up victory conditions
	APGCharacter* PlayerCharacter = Cast<APGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
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

	APGCharacter* MyCharacter{ Cast<APGCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) };
	if (MyCharacter)
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
		APlayerController* PlayerController{ UGameplayStatics::GetPlayerController(this, 0) };
		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, false, false, true, false);
		}
		// Ragdoll the character
		ACharacter* PlayerCharacter{ UGameplayStatics::GetPlayerCharacter(this, 0) };
		if (PlayerCharacter)
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
