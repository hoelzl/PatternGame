// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "Pickup.h"
#include "BatteryPickup.h"
#include "EnergyDrainingPickup.h"
#include "TwoPickupTypesFactory.h"


UTwoPickupTypesFactory::UTwoPickupTypesFactory() :
	Type1Probability{ 0.8f }
{
	CreatedType1 = ABatteryPickup::StaticClass();
	CreatedType2 = AEnergyDrainingPickup::StaticClass();
}

class APickup* UTwoPickupTypesFactory::SpawnPickup(AActor* Owner, APawn* Instigator, FVector Location)
{
	float Rand = FMath::FRand();
	TSubclassOf<APickup> CreatedType = (Rand <= Type1Probability) ? CreatedType1 : CreatedType2;
	return SpawnPickupOfType(CreatedType, Owner, Instigator, Location);
}
