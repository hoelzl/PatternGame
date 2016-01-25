// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "OwenPowerChangingPickupHandler.h"
#include "OwenCharacter.h"


AOwenCharacter::AOwenCharacter()
{
	PowerChangeParameter = FName(TEXT("Coat Color"));
	ConfigureMeshAndAnimation();

	// Ensure that we only create a pickup handler when it is contained in a valid world.
	UWorld* World{ GetWorld() };
	if (ensure(World))
	{
		PickupHandlers.Add(NewObject<UOwenPowerChangingPickupHandler>(World, FName(TEXT("OwenDefaultPickupHandler"))));
	}
}

void AOwenCharacter::ConfigureMeshAndAnimation()
{
	// Configure the skeletal mesh and animation blueprints
	static auto SkeletalMeshName = TEXT("SkeletalMesh'/Game/Characters/Owen/Meshes/Owen.Owen'");
	static auto SkeletalMeshFinder = ConstructorHelpers::FObjectFinder<USkeletalMesh>(SkeletalMeshName);
	if (SkeletalMeshFinder.Succeeded())
	{
		auto MeshComponent = GetMesh();
		MeshComponent->SetSkeletalMesh(SkeletalMeshFinder.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
		MeshComponent->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));

		ConfigureMeshCollision();

	}

	static auto AnimBlueprintName = TEXT("AnimBlueprint'/Game/Characters/Owen/Animations/Owen_AnimBP.Owen_AnimBP_C'");
	static auto AnimBlueprintFinder = ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass>(AnimBlueprintName);
	if (AnimBlueprintFinder.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprintFinder.Object);
	}
}
