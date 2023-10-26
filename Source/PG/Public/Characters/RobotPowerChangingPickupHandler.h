// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Pickups/PickupHandler.h"
#include "RobotPowerChangingPickupHandler.generated.h"

/**
 * A PickupHandler that implements the effect that batteries have on robots.
 */
UCLASS()
class PG_API URobotPowerChangingPickupHandler : public UPickupHandler
{
	GENERATED_BODY()

public:
	virtual bool HandlePickup(AActor* Collector, class APickup* Pickup) override;
};
