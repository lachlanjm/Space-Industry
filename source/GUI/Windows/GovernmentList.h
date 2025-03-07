#ifndef GOVERNMENT_LIST_H
#define GOVERNMENT_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Main\AppState\AppState.h"
#include "..\..\Simulation\Population\Structures\Government.h"

#define BUF_SIZE 64

// TBU FOR MORE LISTS
void drawGovernmentList(AppPlatform* const platform, AppState* const current_app_state, const char* const name);

#endif