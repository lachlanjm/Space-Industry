#ifndef FACTORY_LIST_H
#define FACTORY_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Main\AppState\AppState.h"
#include "..\..\Simulation\Production\Structures\Factory.h"
#include "..\..\Simulation\Production\Enums\ProductionRecipe.h"

#define BUF_SIZE 64

// TBU FOR MORE LISTS
void drawFactoryList(AppPlatform* platform, AppState* current_app_state, char* name);

#endif