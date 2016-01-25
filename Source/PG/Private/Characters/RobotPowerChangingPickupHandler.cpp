// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "PGCharacter.h"
#include "Pickups/Pickup.h"
#include "Pickups/PowerChangingPickup.h"
#include "RobotPowerChangingPickupHandler.h"


bool URobotPowerChangingPickupHandler::HandlePickup(AActor* Collector, APickup* Pickup)
{
    if (Collector && Pickup)
    {
        APowerChangingPickup* PCPickup{ Cast<APowerChangingPickup>(Pickup) };
        APGCharacter* PGCharacter{ Cast<APGCharacter>(Collector) };
        
        if (PCPickup && PGCharacter)
        {
            PGCharacter->UpdatePower(PCPickup->GetBatteryPower());
            return true;
        }
    }
    return false;
}
