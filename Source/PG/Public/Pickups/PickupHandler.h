// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Object.h"
#include "PickupHandler.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PG_API UPickupHandler : public UObject
{
	GENERATED_BODY()
    
public:
    
    UFUNCTION(BlueprintCallable, Category = "Power")
    virtual bool HandlePickup(AActor* Collector, class APickup* Pickup);
};
