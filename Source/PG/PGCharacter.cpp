// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.


#include "PG.h"
#include "PGCharacter.h"
#include "BatteryPickup.h"
#include "Pickup.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

//////////////////////////////////////////////////////////////////////////
// APGCharacter

APGCharacter::APGCharacter() :
    // set our turn rates for input
	BaseTurnRate{ 45.f },
	BaseLookUpRate{ 45.f },
    // Set the dependence of the speed on the power level
    SpeedFactor{ 0.5f },
    BaseSpeed{ 100.0f },
	MaxSpeed{ 800.0f },
	// Set the colors for 0 and full power
	ZeroPowerColor{ FLinearColor::Black },
	FullPowerColor{ FLinearColor::Yellow },
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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// Configure the camera boom
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Configure the follow camera
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	// Configure the collection sphere
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);
	CollectionSphere->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	static FName CollectionSphereCollisionProfile = FName(TEXT("OverlapAllDynamic"));
	CollectionSphere->SetCollisionProfileName(CollectionSphereCollisionProfile);
}


void APGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PowerMaterial = CreateAndApplyPowerMaterial();
}

UMaterialInstanceDynamic* APGCharacter::CreateAndApplyPowerMaterial()
{
	USkeletalMeshComponent* MeshComponent = GetMesh();
	check(MeshComponent && "No mesh component from which to create power material.");

	UMaterialInterface* Material = MeshComponent->GetMaterial(0);
	check(Material && "No material from which to create power material.");

	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	
	MeshComponent->SetMaterial(0, DynamicMaterial);

	return DynamicMaterial;
}


void APGCharacter::UpdatePower(float PowerChange)
{
	CurrentPower += PowerChange;
	float NewSpeed = BaseSpeed + SpeedFactor * CurrentPower;
	GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(NewSpeed, BaseSpeed, MaxSpeed);
	// Apply visual effect
	PowerChangeEffect();
}


void APGCharacter::ConfigureMeshCollision()
{
	auto MeshComponent = GetMesh();
	// TODO: Dynamically switch the collision profiles so that the mesh is toggled between "Character"
	// and "Pawn" depending on whether the capsule registers an overlap.
	static FName MeshCollisionProfile = FName(TEXT("Pawn"));
	static FName CapsuleCollisionProfile = FName(TEXT("Spectator"));
	MeshComponent->SetCollisionProfileName(MeshCollisionProfile);
	GetCapsuleComponent()->SetCollisionProfileName(CapsuleCollisionProfile);
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
			TestPickup->WasCollected(this);
		}
	}
	if (CollectedPower > 0)
	{
		UpdatePower(CollectedPower);
	}
}

void APGCharacter::PowerChangeEffect()
{
	float PowerRatio = FMath::Clamp(CurrentPower / (2 * InitialPower) - 0.33f, 0.f, 1.f);
	FLinearColor Color = UKismetMathLibrary::LinearColorLerp(ZeroPowerColor, FullPowerColor, PowerRatio);

	PowerMaterial->SetVectorParameterValue(PowerChangeParameter, Color);
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
