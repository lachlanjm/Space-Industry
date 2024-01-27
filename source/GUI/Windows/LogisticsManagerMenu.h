#ifndef LOGISTICS_MANAGER_MENU_H
#define LOGISTICS_MANAGER_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Management\Logistics\LogisticsManager.h"
#include "..\..\Simulation\Management\Logistics\LogisticsContract.h"
#include "..\..\Simulation\Transport\Structures\Vehicle.h"

#define BUF_SIZE 64

void drawLogisticsManagerMenu(AppPlatform* platform, LogisticsManager* logisticsManager, char* name);

#endif