// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PGCharacter.h"
#include "OwenCharacter.generated.h"

/**
 * The "Owen" character from the content examples.
 * His coat turns bright yellow if he has lots of energy.
 */
UCLASS()
class PG_API AOwenCharacter : public APGCharacter
{
private:
	GENERATED_BODY()
	
public:
	AOwenCharacter();
	virtual void BeginPlay() override;

private:
	void ConfigureMeshAndAnimation();
	void ConfigureMesh();
	void ConfigureAnimationBlueprint() const;
};
