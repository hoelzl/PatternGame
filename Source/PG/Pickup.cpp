// Copyright 2015 Matthias Hölzl, All Rights Reserved.

#include "PG.h"
#include "Pickup.h"
#include "ConstructorHelpers.h"


// Sets default values
APickup::APickup()
	: // All pickups start active
	  bIsActive{ true },
	  TimeUntilDestruction{ 2.f },
	  TimeBetweenTargetLocationUpdates{ 0.05 }
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	RootComponent = PickupMesh;

	static auto ActivePSTemplateName = TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_electricity_arc.P_electricity_arc'");
	static auto ActivePSFinder = ConstructorHelpers::FObjectFinder<UParticleSystem>(ActivePSTemplateName);
	if (ActivePSFinder.Succeeded())
	{
		ParticleSystemForActivePickupTemplate = ActivePSFinder.Object;
	}
	static auto DestroyedPSTemplateName = TEXT("ParticleSystem'/Game/Environment/Effects/particles/P_Dwarf_Death_Pile_01.P_Dwarf_Death_Pile_01'");
	static auto DestroyedPSFinder = ConstructorHelpers::FObjectFinder<UParticleSystem>(DestroyedPSTemplateName);
	if (DestroyedPSFinder.Succeeded())
	{
		ParticleSystemForDestroyedPickupTemplate = DestroyedPSFinder.Object;
	}
}


void APickup::DestroyPickup()
{
	AActor::GetWorldTimerManager().ClearAllTimersForObject(this);

	if (ParticleSystemForDestroyedPickupTemplate)
	{
		ParticleSystemForDestroyedPickup = UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystemForDestroyedPickupTemplate, GetMeshComponent()->GetComponentLocation(), FRotator::ZeroRotator, true);
	}

	Destroy();
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

void APickup::WasCollected(APGCharacter* Collector)
{
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *GetName());

	PerformPickupAction(Collector);

	if (ParticleSystemForActivePickupTemplate)
	{
		ParticleSystemForActivePickup = UGameplayStatics::SpawnEmitterAttached(ParticleSystemForActivePickupTemplate, GetMeshComponent(), NAME_None, (FVector)ForceInit, FRotator::ZeroRotator, EAttachLocation::SnapToTargetIncludingScale, true);
		UpdateTargetLocationOfParticleSystemForActivePickup();
	}

	FTimerManager &TimerManager = AActor::GetWorldTimerManager();

	FTimerHandle DestructionTimer;
	auto DestructionDelegate = FTimerDelegate::CreateUObject(this, &APickup::DestroyPickup);
	TimerManager.SetTimer(DestructionTimer, DestructionDelegate, TimeUntilDestruction, false);

	FTimerHandle UpdateTimer;
	auto UpdateTargetLocationDelegate = FTimerDelegate::CreateUObject(this, &APickup::UpdateTargetLocationOfParticleSystemForActivePickup);
	TimerManager.SetTimer(UpdateTimer, UpdateTargetLocationDelegate, TimeBetweenTargetLocationUpdates, true);
}

void APickup::UpdateTargetLocationOfParticleSystemForActivePickup()
{
	if (ParticleSystemForActivePickup)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		USkeletalMeshComponent* Mesh = PlayerCharacter->GetMesh();
		FVector SocketLocation = Mesh->GetSocketLocation(TEXT("spine_02"));
		ParticleSystemForActivePickup->SetBeamTargetPoint(0, SocketLocation, 0);
	}
}


void APickup::PerformPickupAction(class APGCharacter* Collector)
{
	SetActive(false);
}
