// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PowerChangingPickup.h"
#include "EnergyDrainingPickup.generated.h"

/**
 * A pickup that drains energy from a character.
 */
UCLASS()
class PG_API AEnergyDrainingPickup : public APowerChangingPickup
{
	GENERATED_BODY()
	
public:
	AEnergyDrainingPickup();
	
};
