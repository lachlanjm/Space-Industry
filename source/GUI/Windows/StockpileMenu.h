#ifndef STOCKPILE_MENU_H
#define STOCKPILE_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Production\Structures\Stockpile.h"

#define BUF_SIZE 64

// TBU FOR MORE LISTS
void drawStockpileMenu(AppPlatform* platform, Stockpile* stockpile, char* name);

#endif