#ifndef ORDER_MENU_H
#define ORDER_MENU_H

#include "..\..\Core\Core.h"
#include "..\..\Simulation\Markets\Structures\Order.h"

#define BUF_SIZE 64

// TBU FOR MORE LISTS
void drawOrderMenu(AppPlatform* platform, Order* order, char* name);

#endif