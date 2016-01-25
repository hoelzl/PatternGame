// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "BatteryPickup.h"
#include "SinglePickupTypeFactory.h"

USinglePickupTypeFactory::USinglePickupTypeFactory()
{
	CreatedType = ABatteryPickup::StaticClass();
}

class APickup* USinglePickupTypeFactory::SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation)
{
	return SpawnPickupOfType(CreatedType, Owner, Instigator, SpawnLocation);
}
