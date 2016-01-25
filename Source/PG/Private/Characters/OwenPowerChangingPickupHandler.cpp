// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "PGCharacter.h"
#include "Pickups/Pickup.h"
#include "Pickups/PowerChangingPickup.h"
#include "OwenPowerChangingPickupHandler.h"

bool UOwenPowerChangingPickupHandler::HandlePickup(AActor* Collector, class APickup* Pickup)
{
	if (Collector && Pickup)
	{
		APowerChangingPickup* PCPickup{ Cast<APowerChangingPickup>(Pickup) };
		APGCharacter* PGCharacter{ Cast<APGCharacter>(Collector) };

		if (PCPickup && PGCharacter)
		{
			PGCharacter->UpdatePower(FMath::Abs(PCPickup->GetBatteryPower()) * 0.5);
			return true;
		}
	}
	return false;
}
