// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "SinglePickupTypeFactory.h"
#include "PickupFactoryComponent.h"


// Sets default values for this component's properties
UPickupFactoryComponent::UPickupFactoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

class APickup* UPickupFactoryComponent::SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation)
{
	if (PickupFactory)
	{
		return PickupFactory->SpawnPickup(Owner, Instigator, SpawnLocation);
	}
	return nullptr;
}