#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

typedef struct PopupWindow PopupWindow;

#include "..\Windows\CompanyList.h"
#include "..\Windows\CompanyMenu.h"
#include "..\Windows\FactoryMenu.h"
#include "..\Windows\GlobalProductMarketList.h"
#include "..\Windows\GlobalProductMarketMenu.h"
#include "..\Windows\GovernmentList.h"
#include "..\Windows\GovernmentMenu.h"
#include "..\Windows\GovernmentMarketMenu.h"
#include "..\Windows\LocalPopulationList.h"
#include "..\Windows\LocalPopulationMenu.h"
#include "..\Windows\LocalProductMarketList.h"
#include "..\Windows\LocalProductMarketMenu.h"
#include "..\Windows\LocationGroup.h"
#include "..\Windows\LocationMenu.h"
#include "..\Windows\LogisticsContractMenu.h"
#include "..\Windows\LogisticsManagerList.h"
#include "..\Windows\LogisticsManagerMenu.h"
#include "..\Windows\MainMenu.h"
#include "..\Windows\OrderMenu.h"
#include "..\Windows\SimulationControlMenu.h"
#include "..\Windows\StockpileMenu.h"
#include "..\Windows\VehicleMenu.h"
#include "..\Enums\WindowTypes.h"

#define BUF_SIZE 64

typedef struct PopupWindow {
	WindowTypes window_type;
	char name[BUF_SIZE];

	union CoreData
	{
		AppState* appState;
		Company* company;
		Factory* factory;
		Government* government;
		LocalPopulation* population;
		TransportNode location;
		LogisticsContract* logisticsContract;
		LogisticsManager* logisticsManager;
		Order* order;
		Product product;
		ProductMarket* productMarket;
		Stockpile* stockpile;
		Vehicle* vehicle;
	} coreData;

	PopupWindow* next;
	PopupWindow* prev;
} PopupWindow;

void assignPopupWindowValues(PopupWindow* window, const WindowTypes window_type, void* coreData);
void drawPopupWindow(PopupWindow* window, AppPlatform* platform);
PopupWindow* addNewPopupWindow(AppPlatform* const platform, const WindowTypes window_type, void* coreData);
void removePopupWindow(PopupWindow* old_window);


#endif