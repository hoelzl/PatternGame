// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Pickup.h"
#include "PickupFactory.h"
#include "SinglePickupTypeFactory.generated.h"

/**
 * A pickup factory that creates a single type of pickup.
 */
UCLASS(AutoExpandCategories = "Spawning")
class PG_API USinglePickupTypeFactory : public UPickupFactory
{
	GENERATED_BODY()

public:
	USinglePickupTypeFactory();

	UPROPERTY(EditAnywhere, NoClear, Category = "Spawning")
	TSubclassOf<APickup> CreatedType;

	virtual APickup* SpawnPickup(AActor* Owner, APawn* Instigator, FVector Location) override;
};
