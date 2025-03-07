#ifndef GLOBAL_PRODUCT_MARKET_MENU_H
#define GLOBAL_PRODUCT_MARKET_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Environment\Structures\MarketMap.h"
#include "..\..\Simulation\Markets\Structures\ProductMarket.h"
#include "..\..\Simulation\Production\Enums\Product.h"
#include "..\..\History\HistoryIterator.h"

#define BUF_SIZE 64

void drawGlobalProductMarketMenu(AppPlatform* const platform, const Product product, const char* const name);

#endif