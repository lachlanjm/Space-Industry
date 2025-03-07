#ifndef COMPANY_MENU_H
#define COMPANY_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Main\AppState\AppState.h"
#include "..\..\Simulation\Management\Production\Company.h"
#include "..\..\Simulation\Production\Enums\ProductionRecipe.h"

#define BUF_SIZE 64

void drawCompanyMenu(AppPlatform* const platform, Company* const company, const char* const name);

#endif