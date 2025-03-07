#ifndef LOCAL_PRODUCT_MARKET_MENU_H
#define LOCAL_PRODUCT_MARKET_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Markets\Structures\Order.h"
#include "..\..\Simulation\Markets\Structures\ProductMarket.h"
#include "..\..\Simulation\Production\Enums\Product.h"
#include "..\..\History\HistoryIterator.h"

#define BUF_SIZE 64

void drawLocalProductMarketMenu(AppPlatform* const platform, ProductMarket* const productMarket, const char* const name);

#endif