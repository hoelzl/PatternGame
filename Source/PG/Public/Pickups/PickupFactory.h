// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Object.h"
#include "Pickup.h"
#include "PickupFactory.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class PG_API UPickupFactory : public UObject
{
	GENERATED_BODY()
	
public:
	virtual APickup* SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation) ;

protected:
	UPickupFactory();

	APickup* SpawnPickupOfType(TSubclassOf<APickup> Type, AActor* Owner, APawn* Instigator, FVector SpawnLocation);
};
