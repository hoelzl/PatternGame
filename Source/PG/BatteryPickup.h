// Copyright (c) 2015, Matthias Hölzl, All Rights Reserved.

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

	// Public way to access the battery's power level
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetBatteryPower() const { return BatteryPower; };

protected:
	// The amount of poser the battery gives to the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BatteryPower;

	virtual void PerformPickupAction(class APGCharacter* Collector) override;
};
