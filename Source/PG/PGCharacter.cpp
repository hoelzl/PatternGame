// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.


#include "PG.h"
#include "PGCharacter.h"
#include "BatteryPickup.h"
#include "Pickup.h"

//////////////////////////////////////////////////////////////////////////
// APGCharacter

APGCharacter::APGCharacter() :
    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom{ CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")) },
    // Create a follow camera
    FollowCamera{ CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")) },
    // Create a collection sphere
    CollectionSphere { CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere")) },
    // set our turn rates for input
	BaseTurnRate{ 45.f },
	BaseLookUpRate{ 45.f },
    // Set the dependence of the speed on the power level
    SpeedFactor{ 0.75f },
    BaseSpeed{ 10.0f },
	// Set a base power level for the character
	InitialPower{ 2000.f },
	CurrentPower{ InitialPower }
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Configure the camera boom
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Configure the follow camera
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Configure the collection sphere
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);
	CollectionSphere->SetRelativeLocation(FVector(100.f, 0.f, 0.f));

	ConfigureMeshAndAnimation();
}

void APGCharacter::UpdatePower(float PowerChange)
{
	CurrentPower += PowerChange;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed + SpeedFactor * CurrentPower;
	// Apply visual effect
	PowerChangeEffect();
}

void APGCharacter::ConfigureMeshAndAnimation()
{
	// Configure the skeletal mesh and animation blueprints
	static auto SkeletalMeshName = TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	static auto SkeletalMeshFinder = ConstructorHelpers::FObjectFinder<USkeletalMesh>(SkeletalMeshName);
	if (SkeletalMeshFinder.Succeeded())
	{
		auto MeshComponent = GetMesh();
		MeshComponent->SetSkeletalMesh(SkeletalMeshFinder.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
		MeshComponent->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));

		// TODO: Dynamically switch the collision profiles so that the mesh is toggled between "Character"
		// and "Pawn" depending on whether the capsule registers an overlap.
		static FName MeshCollisionProfile = FName(TEXT("Pawn"));
		static FName CapsuleCollisionProfile = FName(TEXT("Spectator"));
		MeshComponent->SetCollisionProfileName(MeshCollisionProfile);
		GetCapsuleComponent()->SetCollisionProfileName(CapsuleCollisionProfile);
	}

	static auto AnimBlueprintName = TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'");
	static auto AnimBlueprintFinder = ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass>(AnimBlueprintName);
	if (AnimBlueprintFinder.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprintFinder.Object);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APGCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Collect", IE_Pressed, this, &APGCharacter::CollectPickups);

	InputComponent->BindAxis("MoveForward", this, &APGCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Turn" handles devices that provide an absolute delta, such as a mouse.
	// "TurnrRte" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &APGCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &APGCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &APGCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &APGCharacter::TouchStopped);
}


void APGCharacter::CollectPickups()
{
	// Get all overlapping Actors and store them into an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// Keep track of the collected battery power
	float CollectedPower{ 0.f };

	// For each Actor we collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Cast the Actor to APickup
		APickup* const TestPickup{ Cast<APickup>(CollectedActors[iCollected]) };

		// If the cast is successful and the Pickup is valid and active
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			TestPickup->WasCollected();
			// Check to see if the Pickup is a battery
			ABatteryPickup* const TestBattery{ Cast<ABatteryPickup>(TestPickup) };
			if (TestBattery)
			{
				CollectedPower += TestBattery->GetBatteryPower();
			}
			TestPickup->SetActive(false);
		}
	}
	if (CollectedPower > 0)
	{
		UpdatePower(CollectedPower);
	}
}

void APGCharacter::PowerChangeEffect_Implementation()
{
	auto MeshComponent = GetMesh();
	auto Mesh = MeshComponent->SkeletalMesh;
	auto Material = Mesh->Materials[0];
	auto MaterialInterface = Material.MaterialInterface;
}

void APGCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void APGCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void APGCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APGCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APGCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APGCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
