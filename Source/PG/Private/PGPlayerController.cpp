// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "Characters/PGCharacter.h"
#include "Components/InputComponent.h"
#include "PGPlayerController.h"


APGPlayerController::APGPlayerController()
{
}

void APGPlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	check(InPawn);
	PGCharacter = Cast<APGCharacter>(InPawn);
}

void APGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &APGPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &APGPlayerController::StopJumping);

	InputComponent->BindAction("Collect", IE_Pressed, this, &APGPlayerController::CollectPickups);

	InputComponent->BindAxis("MoveForward", this, &APGPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APGPlayerController::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Turn" handles devices that provide an absolute delta, such as a mouse.
	// "TurnrRte" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APGPlayerController::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &APGPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APGPlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &APGPlayerController::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &APGPlayerController::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &APGPlayerController::TouchStopped);
}

void APGPlayerController::Jump()
{
	if (PGCharacter == nullptr) return;
	PGCharacter->Jump();
}

void APGPlayerController::StopJumping()
{
	if (PGCharacter == nullptr) return;
	PGCharacter->StopJumping();
}

void APGPlayerController::CollectPickups()
{
	if (PGCharacter == nullptr) return;
	PGCharacter->CollectPickups();
}

void APGPlayerController::MoveForward(float Value)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->MoveForward(Value);
}

void APGPlayerController::MoveRight(float Value)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->MoveRight(Value);
}

void APGPlayerController::AddControllerYawInput(float Value)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->AddControllerYawInput(Value);
}

void APGPlayerController::TurnAtRate(float Rate)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->TurnAtRate(Rate);
}

void APGPlayerController::AddControllerPitchInput(float Value)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->AddControllerPitchInput(Value);
}

void APGPlayerController::LookUpAtRate(float Rate)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->LookUpAtRate(Rate);
}

void APGPlayerController::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->TouchStarted(FingerIndex, Location);
}

void APGPlayerController::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (PGCharacter == nullptr) return;
	PGCharacter->TouchStarted(FingerIndex, Location);
}

