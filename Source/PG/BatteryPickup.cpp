// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	Power = 750.0f;

	// Assign a static mesh
	static auto StaticMeshName = TEXT("StaticMesh'/Game/ExampleContent/Blueprint_Communication/Meshes/SM_Battery_Medium.SM_Battery_Medium'");
	static auto MeshFinder = ConstructorHelpers::FObjectFinder<UStaticMesh>(StaticMeshName);
	if (MeshFinder.Succeeded())
	{
		GetMeshComponent()->SetStaticMesh(MeshFinder.Object);
	}
	GetMeshComponent()->SetSimulatePhysics(true);
}

