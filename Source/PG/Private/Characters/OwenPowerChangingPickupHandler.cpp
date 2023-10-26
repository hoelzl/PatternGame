// Copyright (c) 2015, Matthias Hölzl

#include "OwenPowerChangingPickupHandler.h"
#include "PG.h"
#include "PGCharacter.h"
#include "Pickups/Pickup.h"
#include "Pickups/PowerChangingPickup.h"

bool UOwenPowerChangingPickupHandler::HandlePickup(AActor* Collector, class APickup* Pickup)
{
	if (Collector && Pickup)
	{
		const APowerChangingPickup* PCPickup{Cast<APowerChangingPickup>(Pickup)};

		if (APGCharacter * PGCharacter{Cast<APGCharacter>(Collector)}; PCPickup && PGCharacter)
		{
			PGCharacter->UpdatePower(FMath::Abs(PCPickup->GetBatteryPower()) * 0.5);
			return true;
		}
	}
	return false;
}
