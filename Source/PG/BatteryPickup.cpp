// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "BatteryPickup.h"
#include "ConstructorHelpers.h"

ABatteryPickup::ABatteryPickup() :
	// The base power level of the battery
	BatteryPower{ 150.f }
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
