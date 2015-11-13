// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "BatteryPickup.h"
#include "ConstructorHelpers.h"

ABatteryPickup::ABatteryPickup()
{
	// Assign a default static mesh
	static auto StaticMeshName = TEXT("StaticMesh'/Game/ExampleContent/Blueprint_Communication/Meshes/SM_Battery_Medium.SM_Battery_Medium'");
	static auto MeshFinder = ConstructorHelpers::FObjectFinder<class UStaticMesh>(StaticMeshName);
	if (MeshFinder.Succeeded())
	{
		GetMeshComponent()->SetStaticMesh(MeshFinder.Object);
	}
	GetMeshComponent()->SetSimulatePhysics(true);
}

void ABatteryPickup::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
	Destroy();
}
