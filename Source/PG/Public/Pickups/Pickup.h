// Copyright (c) 2015, Matthias Hölzl, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/* 
 * The superclass for all actors that a player can pick up.
 * Typically they will have a (positive or negative) effect on the actor as
 * soon as they are picked up.
 */
UCLASS(Abstract)
class PG_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Return the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMeshComponent() const { return PickupMesh; };

	// Return whether or not the Pickup is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	// Allows other classes to safely change whether or not the pickup is active
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

	// Function to call when the pickup is collected
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual void WasCollected(class APGCharacter* Collector);

protected:
	// Sets default values for this actor's properties
	APickup();
    
    // True when the pickup can be used, false when the pickup is deactivated
    bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float TimeUntilDestruction;

	// Destroy all timers and then this actor
	virtual void DestroyPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	UParticleSystem* ParticleSystemForActivePickupTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	UParticleSystemComponent* ParticleSystemForActivePickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float TimeBetweenTargetLocationUpdates;

	UFUNCTION(BlueprintCallable, Category = "Power")
	virtual void UpdateTargetLocationOfParticleSystemForActivePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	UParticleSystem* ParticleSystemForDestroyedPickupTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	UParticleSystemComponent* ParticleSystemForDestroyedPickup;

private:
	// Static mesh to represent the pickup in the level.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
};
