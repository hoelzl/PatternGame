// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "RobotCharacter.h"


ARobotCharacter::ARobotCharacter()
{
	ConfigureMeshAndAnimation();
}

void ARobotCharacter::ConfigureMeshAndAnimation()
{
	// Configure the skeletal mesh and animation blueprints
	static auto SkeletalMeshName = TEXT("SkeletalMesh'/Game/Characters/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	static auto SkeletalMeshFinder = ConstructorHelpers::FObjectFinder<USkeletalMesh>(SkeletalMeshName);
	if (SkeletalMeshFinder.Succeeded())
	{
		auto MeshComponent = GetMesh();
		MeshComponent->SetSkeletalMesh(SkeletalMeshFinder.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
		MeshComponent->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));

		ConfigureMeshCollision();

	}

	static auto AnimBlueprintName = TEXT("AnimBlueprint'/Game/Characters/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'");
	static auto AnimBlueprintFinder = ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass>(AnimBlueprintName);
	if (AnimBlueprintFinder.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprintFinder.Object);
	}
}
