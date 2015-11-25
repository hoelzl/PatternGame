// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "SpawnVolume.h"
#include "PickupFactory.h"
#include "SinglePickupTypeFactory.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume() : 
	// Set the spawn delay range
	SpawnDelayRangeLow{ 1.0f },
	SpawnDelayRangeHigh{ 4.5f }
{
	PrimaryActorTick.bCanEverTick = false;

	// PickupFactory = CreateDefaultSubobject<ASinglePickupTypeFactory>(TEXT("PickupFactory"));

	// Create the BoxComponent to represent the spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin{ WhereToSpawn->Bounds.Origin };
	FVector SpawnExtent{ WhereToSpawn->Bounds.BoxExtent };

	return UKismetMathLibrary::RandomPointInBoundingBox( SpawnOrigin, SpawnExtent );
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		UpdateSpawnTimer();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup()
{
	PickupFactory->SpawnPickup(this, Instigator, GetRandomPointInVolume());
	UpdateSpawnTimer();
}

void ASpawnVolume::UpdateSpawnTimer()
{
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

