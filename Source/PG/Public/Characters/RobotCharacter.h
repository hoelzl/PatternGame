// Copyright (c) 2015, Matthias Hölzl

#pragma once

#include "PGCharacter.h"
#include "RobotCharacter.generated.h"

/**
 * The default UE4 pawn (aka Tim Plate) as playable character.
 * Turns bright yellow if it has lots of power and black when power is running low.
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
