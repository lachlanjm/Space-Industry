#ifndef COMPANY_LIST_H
#define COMPANY_LIST_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Main\AppState\AppState.h"
#include "..\..\Simulation\Management\Production\Company.h"

#define BUF_SIZE 64

// TBU FOR MORE LISTS
void drawCompanyList(AppPlatform* platform, AppState* current_app_state, char* name);

#endif