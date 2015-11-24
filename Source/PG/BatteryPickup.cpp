// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "BatteryPickup.h"
#include "PGCharacter.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ABatteryPickup::ABatteryPickup() :
	// The base power level of the battery
	BatteryPower{ 750.f }
{
	// Assign a default static mesh
	static auto StaticMeshName = TEXT("StaticMesh'/Game/ExampleContent/Blueprint_Communication/Meshes/SM_Battery_Medium.SM_Battery_Medium'");
	static auto MeshFinder = ConstructorHelpers::FObjectFinder<UStaticMesh>(StaticMeshName);
	if (MeshFinder.Succeeded())
	{
		GetMeshComponent()->SetStaticMesh(MeshFinder.Object);
	}
	GetMeshComponent()->SetSimulatePhysics(true);
}

void ABatteryPickup::PerformPickupAction(APGCharacter* Collector)
{
	if (Collector)
	{
		Collector->UpdatePower(BatteryPower);
	}
}

