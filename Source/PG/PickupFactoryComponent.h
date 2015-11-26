// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "Components/ActorComponent.h"
#include "PickupFactory.h"
#include "PickupFactoryComponent.generated.h"


UCLASS()
class PG_API UPickupFactoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupFactoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Spawning")
	UPickupFactory* PickupFactory;

	class APickup* SpawnPickup(AActor* Owner, APawn* Instigator, FVector SpawnLocation);
};
