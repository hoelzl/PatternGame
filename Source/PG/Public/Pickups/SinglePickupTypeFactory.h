// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PickupFactory.h"
#include "Pickup.h"
#include "SinglePickupTypeFactory.generated.h"

/**
 * 
 */
UCLASS(AutoExpandCategories = "Spawning")
class PG_API USinglePickupTypeFactory : public UPickupFactory
{
	GENERATED_BODY()

public:
	USinglePickupTypeFactory();

	UPROPERTY(EditAnywhere, NoClear, Category = "Spawning")
	TSubclassOf<APickup> CreatedType;
	
	APickup* SpawnPickup(AActor* Owner, APawn* Instigator, FVector Location) override;
};
