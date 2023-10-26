// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "SpawnVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PG.h"
#include "PGGameMode.h"
#include "Pickups/SinglePickupTypeFactory.h"

// Sets default values
ASpawnVolume::ASpawnVolume() : SpawnDelayRangeLow{1.0f}, SpawnDelayRangeHigh{4.5f}
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the BoxComponent to represent the spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	const UWorld* World = GetWorld();
	check(World && "Spawned actor while world does not exist?");

	if (APGGameMode * GameMode{Cast<APGGameMode>(UGameplayStatics::GetGameMode(this))}; GameMode && IsValid(GameMode))
	{
		GameMode->RegisterSpawnVolume(this);
	}
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	const FVector SpawnOrigin{WhereToSpawn->Bounds.Origin};
	const FVector SpawnExtent{WhereToSpawn->Bounds.BoxExtent};

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
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
	if (PickupFactory)
	{
		PickupFactory->SpawnPickup(this, GetInstigator(), GetRandomPointInVolume());
		UpdateSpawnTimer();
	}
}

void ASpawnVolume::UpdateSpawnTimer()
{
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}
