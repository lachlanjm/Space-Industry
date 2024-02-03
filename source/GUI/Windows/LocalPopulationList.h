#ifndef LOCAL_POPULATION_LIST_H
#define LOCAL_POPULATION_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Main\AppState\AppState.h"
#include "..\..\Simulation\Population\Structures\LocalPopulation.h"

#define BUF_SIZE 64

void drawLocalPopulationList(AppPlatform* platform, AppState* current_app_state, char* name);

#endif