// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PickupHandler.h"
#include "OwenPowerChangingPickupHandler.generated.h"

/**
 * 
 */
UCLASS()
class PG_API UOwenPowerChangingPickupHandler : public UPickupHandler
{
	GENERATED_BODY()
	
public:
	virtual bool HandlePickup(AActor* Collector, class APickup* Pickup) override;
	
};
