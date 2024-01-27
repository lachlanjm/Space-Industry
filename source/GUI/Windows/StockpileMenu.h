#ifndef STOCKPILE_MENU_H
#define STOCKPILE_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Production\Structures\Stockpile.h"
#include "..\..\Simulation\Production\Enums\Product.h"

#define BUF_SIZE 64

void drawStockpileMenu(AppPlatform* platform, Stockpile* stockpile, char* name);

#endif