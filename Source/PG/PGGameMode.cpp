// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "PGGameMode.h"
#include "PGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

APGGameMode::APGGameMode() :
	DecayRate{ 0.05f },
	PowerToWinFactor{ 2.f }
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

void APGGameMode::BeginPlay()
{
	Super::BeginPlay();

	APGCharacter* PlayerCharacter = Cast<APGCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		PowerToWin = PowerToWinFactor * PlayerCharacter->GetInitialPower();
	}
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void APGGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APGCharacter* MyCharacter{ Cast<APGCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)) };
	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentPower() > 0)
		{
			MyCharacter->UpdatePower(-DeltaTime * DecayRate * MyCharacter->GetInitialPower());
		}
	}
}

float APGGameMode::GetPowerToWin() const
{
	return PowerToWin;
}
