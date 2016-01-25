// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PGCharacter.h"
#include "RobotCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PG_API ARobotCharacter : public APGCharacter
{
	GENERATED_BODY()
	
public:
	ARobotCharacter();
	
private:

	/** Provide defaults for the mesh and animations */
	void ConfigureMeshAndAnimation();

};
