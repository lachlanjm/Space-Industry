#ifndef VEHICLE_MENU_H
#define VEHICLE_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Transport\Structures\Vehicle.h"
#include "..\..\Simulation\Environment\Enums\TransportNode.h"

#define BUF_SIZE 64

void drawVehicleMenu(AppPlatform* platform, Vehicle* vehicle, char* name);

#endif