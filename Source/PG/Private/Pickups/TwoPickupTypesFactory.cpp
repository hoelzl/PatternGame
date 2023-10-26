// Copyright (c) 2015, Matthias Hölzl

#include "TwoPickupTypesFactory.h"
#include "BatteryPickup.h"
#include "EnergyDrainingPickup.h"
#include "PG.h"
#include "Pickup.h"

UTwoPickupTypesFactory::UTwoPickupTypesFactory() : Type1Probability{0.8f}
{
	CreatedType1 = ABatteryPickup::StaticClass();
	CreatedType2 = AEnergyDrainingPickup::StaticClass();
}

class APickup* UTwoPickupTypesFactory::SpawnPickup(AActor* Owner, APawn* Instigator, FVector Location)
{
	const float RandomUnitValue{FMath::FRand()};
	const TSubclassOf<APickup> CreatedType{(RandomUnitValue <= Type1Probability) ? CreatedType1 : CreatedType2};
	return SpawnPickupOfType(CreatedType, Owner, Instigator, Location);
}
