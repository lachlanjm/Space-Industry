#ifndef LOCAL_POPULATION_MENU_H
#define LOCAL_POPULATION_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Population\Structures\LocalPopulation.h"

#define BUF_SIZE 64

void drawLocalPopulationMenu(AppPlatform* platform, LocalPopulation* population, char* name);

#endif