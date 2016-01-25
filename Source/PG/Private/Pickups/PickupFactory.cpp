// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "PickupFactory.h"


class APickup* UPickupFactory::SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation)
{
	UE_LOG(LogClass, Warning, TEXT("Trying to use direct instance of UPickupFactory"));
	return nullptr;
}


UPickupFactory::UPickupFactory()
{
}

class APickup* UPickupFactory::SpawnPickupOfType(TSubclassOf<APickup> Type, AActor* Owner, APawn* Instigator, FVector SpawnLocation)
{
	if (Type != nullptr)
	{
		UWorld* const World = Owner->GetWorld();
		if (World)
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



