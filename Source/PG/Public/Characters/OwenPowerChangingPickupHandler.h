// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Pickups/PickupHandler.h"
#include "OwenPowerChangingPickupHandler.generated.h"

/**
 * A handler for power-changing pickups for Owen.
 * Always applies the pickup power change as health gain, but multiplies
 * the value with 0.5
 */
UCLASS()
class PG_API UOwenPowerChangingPickupHandler : public UPickupHandler
{
	GENERATED_BODY()

public:
	virtual bool HandlePickup(AActor* Collector, class APickup* Pickup) override;
};
