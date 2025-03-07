#ifndef GLOBAL_PRODUCT_MARKET_LIST_H
#define GLOBAL_PRODUCT_MARKET_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Environment\Structures\MarketMap.h"
#include "..\..\Simulation\Production\Enums\Product.h"

#define BUF_SIZE 64

void drawGlobalProductMarketList(AppPlatform* const platform, AppState* const current_app_state, const char* const name);

#endif