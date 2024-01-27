#ifndef LOGISTICS_CONTRACT_MENU_H
#define LOGISTICS_CONTRACT_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Management\Logistics\LogisticsContract.h"
#include "..\..\Simulation\Production\Enums\Product.h"
#include "..\..\Simulation\Production\Structures\Factory.h"
#include "..\..\Simulation\Transport\Structures\Vehicle.h"

#define BUF_SIZE 64

void drawLogisticsContractMenu(AppPlatform* platform, LogisticsContract* logisticsContract, char* name);

#endif