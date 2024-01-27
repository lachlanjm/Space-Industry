#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

typedef struct PopupWindow PopupWindow;

#include "..\Windows\FactoryList.h"
#include "..\Windows\FactoryMenu.h"
#include "..\Windows\LocationGroup.h"
#include "..\Windows\LocationMenu.h"
#include "..\Windows\MainMenu.h"
#include "..\Windows\OrderMenu.h"
#include "..\Windows\ProductMarketList.h"
#include "..\Windows\ProductMarketMenu.h"
#include "..\Windows\StockpileMenu.h"
#include "..\Windows\VehicleMenu.h"
#include "..\Enums\WindowTypes.h"

#define BUF_SIZE 64

typedef struct PopupWindow {
	WindowTypes window_type;
	char name[BUF_SIZE];

	void* struct_ptr;
	union CoreData
	{
		AppState* appState;
		Factory* factory;
		TransportNode location;
		Order* order;
		ProductMarket* productMarket;
		Stockpile* stockpile;
		Vehicle* vehicle;
	} coreData;

	PopupWindow* next;
	PopupWindow* prev;
} PopupWindow;

void assignPopupWindowValues(PopupWindow* window, WindowTypes window_type, void* coreData);
void drawPopupWindow(PopupWindow* window, AppPlatform* platform);
PopupWindow* addNewPopupWindow(PopupWindow* first_window, WindowTypes window_type, void* coreData);
void removePopupWindow(PopupWindow* old_window);


#endif