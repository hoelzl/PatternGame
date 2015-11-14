// Copyright (c) 2015, Matthias Hölzl, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
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
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();
	virtual void WasCollected_Implementation();

protected:
	// Sets default values for this actor's properties
	APickup();

	// True when the pickup can be used, false when the pickup is deactivated
	bool bIsActive;

private:
	// Static mesh to represent the pickup in the level.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
};
