#ifndef GOVERNMENT_PRODUCT_MARKET_MENU_H
#define GOVERNMENT_PRODUCT_MARKET_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Population\Structures\Government.h"
#include "..\..\History\HistoryIterator.h"

#define BUF_SIZE 64

void drawGovernmentMarketMenu(AppPlatform* const platform, Government* const government, const char* const name);

#endif