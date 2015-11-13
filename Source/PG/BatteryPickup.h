// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * A pickup that provides power and is visually represented as battery
 */
UCLASS()
class PG_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this battery's properties
	ABatteryPickup();

	// Override WasCollected function - use Implementation because it's a Blueprint Native Event
	void WasCollected_Implementation() override;
};
