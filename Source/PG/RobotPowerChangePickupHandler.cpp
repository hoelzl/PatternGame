// Copyright (c) 2015, Matthias Hölzl

#include "PG.h"
#include "PGCharacter.h"
#include "Pickup.h"
#include "PowerChangingPickup.h"
#include "RobotPowerChangePickupHandler.h"


bool URobotPowerChangePickupHandler::HandlePickup(AActor* Collector, APickup* Pickup)
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
