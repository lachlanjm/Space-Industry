#ifndef GOVERNMENT_MENU_H
#define GOVERNMENT_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Population\Structures\Government.h"

#define BUF_SIZE 64

void drawGovernmentMenu(AppPlatform* const platform, Government* const government, const char* const name);

#endif