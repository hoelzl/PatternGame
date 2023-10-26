// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "Pickup.h"
#include "ConstructorHelpers.h"
#include "PG.h"
#include "PickupCollector.h"

// Sets default values
APickup::APickup()
	: // All pickups start active
	bIsActive{true}
	, TimeUntilDestruction{2.f}
	, TimeBetweenTargetLocationUpdates{0.05}
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = PickupMesh;

	static auto ActivePSTemplateName =
		TEXT("ParticleSystem'/Game/Effects/ParticleSystems/P_electricity_arc.P_electricity_arc'");
	static auto ActivePSFinder = ConstructorHelpers::FObjectFinder<UParticleSystem>(ActivePSTemplateName);
	if (ActivePSFinder.Succeeded())
	{
		ParticleSystemForActivePickupTemplate = ActivePSFinder.Object;
	}
	static auto DestroyedPSTemplateName =
		TEXT("ParticleSystem'/Game/Effects/ParticleSystems/P_Dwarf_Death_Pile_01.P_Dwarf_Death_Pile_01'");
	static auto DestroyedPSFinder = ConstructorHelpers::FObjectFinder<UParticleSystem>(DestroyedPSTemplateName);
	if (DestroyedPSFinder.Succeeded())
	{
		ParticleSystemForDestroyedPickupTemplate = DestroyedPSFinder.Object;
	}
}

void APickup::ApplyAndDestroyPickup()
{
	AActor::GetWorldTimerManager().ClearAllTimersForObject(this);

	if (ParticleSystemForDestroyedPickupTemplate)
	{
		ParticleSystemForDestroyedPickup = UGameplayStatics::SpawnEmitterAtLocation(
			this, ParticleSystemForDestroyedPickupTemplate, GetMeshComponent()->GetComponentLocation(),
			FRotator::ZeroRotator, true);
	}

	if (Collector)
	{
		Collector->HandlePickup(this);
	}

	Destroy();
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool APickup::IsActive() const
{
	return bIsActive;
}

void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup::WasCollected(TScriptInterface<IPickupCollector> InCollector)
{
	UE_LOG(PG, Log, TEXT("You have collected %s"), *GetName());

	SetActive(false);
	Collector = InCollector;

	if (ParticleSystemForActivePickupTemplate)
	{
		ParticleSystemForActivePickup = UGameplayStatics::SpawnEmitterAttached(
			ParticleSystemForActivePickupTemplate, GetMeshComponent(), NAME_None, static_cast<FVector>(ForceInit),
			FRotator::ZeroRotator, EAttachLocation::SnapToTargetIncludingScale, true);
		UpdateTargetLocationOfParticleSystemForActivePickup();
	}

	FTimerManager& TimerManager = AActor::GetWorldTimerManager();

	FTimerHandle DestructionTimer;
	const auto DestructionDelegate{FTimerDelegate::CreateUObject(this, &APickup::ApplyAndDestroyPickup)};
	TimerManager.SetTimer(DestructionTimer, DestructionDelegate, TimeUntilDestruction, false);

	FTimerHandle UpdateTimer;
	const auto UpdateTargetLocationDelegate{
		FTimerDelegate::CreateUObject(this, &APickup::UpdateTargetLocationOfParticleSystemForActivePickup)};
	TimerManager.SetTimer(UpdateTimer, UpdateTargetLocationDelegate, TimeBetweenTargetLocationUpdates, true);

	InCollector->HandlePickup(this);
}

void APickup::UpdateTargetLocationOfParticleSystemForActivePickup()
{
	if (ParticleSystemForActivePickup)
	{
		const ACharacter* PlayerCharacter{UGameplayStatics::GetPlayerCharacter(this, 0)};
		const USkeletalMeshComponent* Mesh{PlayerCharacter->GetMesh()};
		const FVector SocketLocation{Mesh->GetSocketLocation(TEXT("spine_02"))};
		ParticleSystemForActivePickup->SetBeamTargetPoint(0, SocketLocation, 0);
	}
}
