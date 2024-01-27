#ifndef PRODUCT_MARKET_LIST_H
#define PRODUCT_MARKET_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Environment\Enums\TransportNode.h"
#include "..\..\Simulation\Environment\Structures\MarketMap.h"
#include "..\..\Simulation\Production\Enums\Product.h"

#define BUF_SIZE 64

void drawProductMarketList(AppPlatform* platform, TransportNode location, char* name);

#endif