// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"


// Sets default values
ASpawnVolume::ASpawnVolume() : 
	// Create the BoxComponent to represent the spawn volume
	WhereToSpawn{ CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn")) },
	// Set the spawn delay range
	SpawnDelayRangeLow{1.0f},
	SpawnDelayRangeHigh{4.5f}
{
	PrimaryActorTick.bCanEverTick = false;
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
	if (WhatToSpawn != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetRandomPointInVolume();

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			APickup* const SpawnedPickup{ World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams)};
			UpdateSpawnTimer();
		}
	}
}

void ASpawnVolume::UpdateSpawnTimer()
{
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

