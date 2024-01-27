#ifndef LOGISTICS_MANAGER_LIST_H
#define LOGISTICS_MANAGER_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Main\AppState\AppState.h"
#include "..\..\Simulation\Management\Logistics\LogisticsManager.h"

#define BUF_SIZE 64

void drawLogisticsManagerList(AppPlatform* platform, AppState* current_app_state, char* name);

#endif