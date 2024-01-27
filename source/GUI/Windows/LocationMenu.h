#ifndef LOCATION_MENU_H
#define LOCATION_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Environment\Enums\TransportNode.h"

#define BUF_SIZE 64

// TBU FOR MORE LISTS
void drawLocationMenu(AppPlatform* platform, TransportNode* location, char* name);

#endif