// Copyright (c) 2015, Matthias Hölzl, All Rights Reserved.

#pragma once

#include "PowerChangingPickup.h"
#include "BatteryPickup.generated.h"

/**
 * A pickup that provides power and is visually represented as battery
 */
UCLASS()
class PG_API ABatteryPickup : public APowerChangingPickup
{
	GENERATED_BODY()
	
public:
	// Sets default values for this battery's properties
	ABatteryPickup();

};
