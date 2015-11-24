// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "BatteryPickup.h"
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

	static auto ParticleSystemTemplateName = TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_electricity_arc.P_electricity_arc'");
	static auto PSFinder = ConstructorHelpers::FObjectFinder<UParticleSystem>(ParticleSystemTemplateName);
	if (PSFinder.Succeeded())
	{
		ParticleSystemTemplate = PSFinder.Object;
	}
}


void ABatteryPickup::DestroyBattery()
{
	AActor::GetWorldTimerManager().ClearAllTimersForObject(this);
	Destroy();
}

void ABatteryPickup::WasCollected()
{
	Super::WasCollected();

	ParticleSystem = UGameplayStatics::SpawnEmitterAttached(ParticleSystemTemplate, GetMeshComponent(), NAME_None, (FVector)ForceInit, FRotator::ZeroRotator, EAttachLocation::SnapToTargetIncludingScale, true);
	UpdateParticleSystemTargetLocation();

	FTimerManager &TimerManager = AActor::GetWorldTimerManager();
	
	FTimerHandle DestructionTimer;
	auto DestructionDelegate = FTimerDelegate::CreateUObject(this, &ABatteryPickup::DestroyBattery);
	TimerManager.SetTimer(DestructionTimer, DestructionDelegate, 2.f, false);

	FTimerHandle UpdateTimer;
	auto UpdateTargetLocationDelegate = FTimerDelegate::CreateUObject(this, &ABatteryPickup::UpdateParticleSystemTargetLocation);
	TimerManager.SetTimer(UpdateTimer, UpdateTargetLocationDelegate, 0.05, true);
}

void ABatteryPickup::UpdateParticleSystemTargetLocation()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	USkeletalMeshComponent* Mesh = PlayerCharacter->GetMesh();
	FVector SocketLocation = Mesh->GetSocketLocation(TEXT("spine_02"));
	ParticleSystem->SetBeamTargetPoint(0, SocketLocation, 0);
}
