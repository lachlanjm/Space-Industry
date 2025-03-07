#ifndef LOCATION_MENU_H
#define LOCATION_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Environment\Enums\TransportNode.h"
#include "..\..\Simulation\Environment\Enums\TransportConnectionType.h"
#include "..\..\Simulation\Environment\Structures\MarketMap.h"
#include "..\..\Simulation\Environment\Structures\Map.h"
#include "..\..\Simulation\Population\Structures\Government.h"
#include "..\..\Simulation\Population\Structures\LocalPopulation.h"

#define BUF_SIZE 64

void drawLocationMenu(AppPlatform* platform, TransportNode location, char* name);

#endif