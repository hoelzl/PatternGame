// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Pickup.h"
#include "PowerChangingPickup.generated.h"

/**
 * A pickup that changes a character's power level.
 */
UCLASS(Abstract)
class PG_API APowerChangingPickup : public APickup
{
	GENERATED_BODY()

public:
	APowerChangingPickup();

	// Public way to access the battery's power level
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetBatteryPower() const { return Power; };

protected:
	// The amount of poser the battery gives to the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float Power;
};
