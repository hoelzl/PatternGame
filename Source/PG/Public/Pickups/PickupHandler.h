// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Object.h"
#include "PickupHandler.generated.h"

/**
 * A handler for pickups.
 * The combination of a character's pickup handlers and the picked-up item determine the effect
 * the item has on the character.
 */
UCLASS()
class PG_API UPickupHandler : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Power")
	virtual bool HandlePickup(AActor* Collector, class APickup* Pickup);
};
