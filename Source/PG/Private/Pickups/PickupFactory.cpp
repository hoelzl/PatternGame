// Copyright (c) 2015, Matthias Hölzl

#include "PickupFactory.h"
#include "PG.h"

class APickup* UPickupFactory::SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation)
{
	UE_LOG(PG, Warning, TEXT("Trying to use direct instance of UPickupFactory"));
	return nullptr;
}

UPickupFactory::UPickupFactory()
{
}

class APickup* UPickupFactory::SpawnPickupOfType(TSubclassOf<APickup> Type, AActor* Owner, APawn* Instigator,
												 const FVector& SpawnLocation)
{
	if (Type != nullptr)
	{
		if (UWorld* const World = Owner->GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = Owner;
			SpawnParams.Instigator = Instigator;

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			return World->SpawnActor<APickup>(Type, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
	return nullptr;
}
