// Copyright (c) 2020, Matthias Hölzl

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupCollector.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UPickupCollector : public UInterface
{
	GENERATED_BODY()
};

class APickup;

/**
 * Interface inherited by all actors that can handle pickups.
 */
class PG_API IPickupCollector
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Pickup)
	virtual void HandlePickup(APickup* Pickup) = 0;
};
