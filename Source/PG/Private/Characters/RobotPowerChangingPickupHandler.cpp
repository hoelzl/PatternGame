// Copyright (c) 2015, Matthias Hölzl

#include "RobotPowerChangingPickupHandler.h"
#include "PG.h"
#include "PGCharacter.h"
#include "Pickups/Pickup.h"
#include "Pickups/PowerChangingPickup.h"

bool URobotPowerChangingPickupHandler::HandlePickup(AActor* Collector, APickup* Pickup)
{
	if (Collector && Pickup)
	{
		const APowerChangingPickup* PCPickup{Cast<APowerChangingPickup>(Pickup)};
		APGCharacter* PGCharacter{Cast<APGCharacter>(Collector)};

		if (PCPickup && PGCharacter)
		{
			PGCharacter->UpdatePower(PCPickup->GetBatteryPower());
			return true;
		}
	}
	return false;
}
