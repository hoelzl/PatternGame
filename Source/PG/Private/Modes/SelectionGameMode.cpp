// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "Modes/SelectionGameMode.h"
#include "PGPlayerController.h"
#include "PGGameInstance.h"
#include "Characters/RobotCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ASelectionGameMode::ASelectionGameMode() :
	NextLevelName{ FName(TEXT("CollectionLevel")) }
{
	DefaultPawnClass = ARobotCharacter::StaticClass();
	PlayerControllerClass = APGPlayerController::StaticClass();

	static auto HUDBlueprintClassName = TEXT("WidgetBlueprint'/Game/Blueprints/SelectionHUD.SelectionHUD_C'");
	static auto HUDFinder = ConstructorHelpers::FClassFinder<UUserWidget>(HUDBlueprintClassName);
	if (HUDFinder.Succeeded())
	{
		HUDWidgetClass = HUDFinder.Class;
	}
}

void ASelectionGameMode::BeginPlay()
{
	if (HUDWidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget != nullptr)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void ASelectionGameMode::SelectCharacter(APGCharacter* Character)
{
	UGameInstance* GameInstance = GetGameInstance();
	check(GameInstance != nullptr && "Could not retreive a game instance?");
	UPGGameInstance* PGGameInstance = Cast<UPGGameInstance>(GameInstance);
	check(PGGameInstance);
	PGGameInstance->PlayerCharacterClass = Character->GetClass();
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}
