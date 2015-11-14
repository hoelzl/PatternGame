// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "Pickup.h"
#include "ConstructorHelpers.h"


// Sets default values
APickup::APickup()
	: // All pickups start active
	  bIsActive{true},
	  PickupMesh{CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh")}
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup::WasCollected_Implementation()
{
	// Log a debug message
	FString PickupDebugString{ GetName() };
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}

