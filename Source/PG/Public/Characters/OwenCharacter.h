// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PGCharacter.h"
#include "OwenCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PG_API AOwenCharacter : public APGCharacter
{
	GENERATED_BODY()
	
public:
	AOwenCharacter();

private:

	/** Provide defaults for the mesh and animations */
	void ConfigureMeshAndAnimation();
};
