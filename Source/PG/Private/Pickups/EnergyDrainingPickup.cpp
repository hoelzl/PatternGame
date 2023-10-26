// Copyright (c) 2015, Matthias Hölzl

#include "EnergyDrainingPickup.h"
#include "ConstructorHelpers.h"
#include "PG.h"

AEnergyDrainingPickup::AEnergyDrainingPickup()
{
	Power = -250.f;

	// Assign a default static mesh
	static auto StaticMeshName = TEXT("StaticMesh'/Game/Props/Battery/Meshes/SM_Drainer_Medium.SM_Drainer_Medium'");
	static auto MeshFinder = ConstructorHelpers::FObjectFinder<UStaticMesh>(StaticMeshName);
	if (MeshFinder.Succeeded())
	{
		GetMeshComponent()->SetStaticMesh(MeshFinder.Object);
	}
	GetMeshComponent()->SetSimulatePhysics(true);
}
