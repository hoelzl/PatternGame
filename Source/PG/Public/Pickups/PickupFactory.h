// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Object.h"
#include "Pickup.h"
#include "PickupFactory.generated.h"

/**
 * A generic factory for pickups.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class PG_API UPickupFactory : public UObject
{
	GENERATED_BODY()

public:
	virtual APickup* SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation);

protected:
	UPickupFactory();

	static APickup* SpawnPickupOfType(TSubclassOf<APickup> Type, AActor* Owner, APawn* Instigator,
									  const FVector& SpawnLocation);
};
