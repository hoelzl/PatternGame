// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "PowerChangingPickup.h"
#include "PGCharacter.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


APowerChangingPickup::APowerChangingPickup() :
	// The power level of this pickup
	Power{ 0.f }
{
}
