// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PickupFactory.h"
#include "Pickup.h"
#include "TwoPickupTypesFactory.generated.h"

/**
 * A pickup factory that generates two kinds of pickups in a ratio that can be set by the user.
 */
UCLASS(AutoExpandCategories = "Spawning")
class PG_API UTwoPickupTypesFactory : public UPickupFactory
{
	GENERATED_BODY()
	
public:
	UTwoPickupTypesFactory();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, NoClear, Category = "Spawning")
	TSubclassOf<APickup> CreatedType1;

	// The probability of creating CreatedType1, in the range 0.0 .. 1.0
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawning")
	float Type1Probability;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, NoClear, Category = "Spawning")
	TSubclassOf<APickup> CreatedType2;

	virtual class APickup* SpawnPickup(AActor* Owner, APawn* Instigator, FVector Location) override;
};
