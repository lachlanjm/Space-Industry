#include "PopupWindow.h"

static void appendPopupWindow(PopupWindow* base_window, PopupWindow* new_window);

static void castCoreData(PopupWindow* window, WindowTypes window_type, void* coreData)
{
	switch (window->window_type)
	{
	case FACTORY_LIST:
	case LOCATION_GROUP:
	case MAIN_MENU:
		window->coreData.appState = coreData;
		break;
	
	case FACTORY:
		window->coreData.factory = coreData;
		break;

	case LOCATION:
	case PRODUCT_MARKET_LIST:
		window->coreData.location = *((TransportNode*) coreData);
		break;

	case ORDER:
		window->coreData.order = coreData;
		break;

	case PRODUCT_MARKET:
		window->coreData.productMarket = coreData;
		break;

	case STOCKPILE:
		window->coreData.stockpile = coreData;
		break;

	case VEHICLE:
		window->coreData.vehicle = coreData;
		break;
	
	default:
		window->coreData.appState = NULL;
		break;
	}
}

void assignPopupWindowValues(PopupWindow* window, WindowTypes window_type, void* coreData)
{
	static int id = 0;
	window->window_type = window_type;
	snprintf(window->name, BUF_SIZE, "%d", id++);
	castCoreData(window, window_type, coreData);
	window->next = NULL;
	window->prev = NULL;
}

void drawPopupWindow(PopupWindow* window, AppPlatform* platform)
{
	switch (window->window_type)
	{
	case FACTORY_LIST:
		drawFactoryList(platform, window->coreData.appState, window->name);
		break;
	
	case FACTORY:
		drawFactoryMenu(platform, window->coreData.factory, window->name);
		break;

	case LOCATION_GROUP:
		drawLocationGroup(platform, window->coreData.appState, window->name);
		break;

	case LOCATION:
		drawLocationMenu(platform, window->coreData.location, window->name);
		break;
	
	case MAIN_MENU:
		drawMainMenu(platform, window->coreData.appState, window->name);
		break;

	case ORDER:
		drawOrderMenu(platform, window->coreData.order, window->name);
		break;
	
	case PRODUCT_MARKET_LIST:
		drawProductMarketList(platform, window->coreData.location, window->name);
		break;

	case PRODUCT_MARKET:
		drawProductMarketMenu(platform, window->coreData.productMarket, window->name);
		break;

	case STOCKPILE:
		drawStockpileMenu(platform, window->coreData.stockpile, window->name);
		break;

	case VEHICLE:
		drawVehicleMenu(platform, window->coreData.vehicle, window->name);
		break;
	
	default:
		break;
	}
}

PopupWindow* addNewPopupWindow(PopupWindow* first_window, WindowTypes window_type, void* coreData)
{
	PopupWindow* new_window = calloc(1, sizeof(PopupWindow));

	assignPopupWindowValues(new_window, window_type, coreData);
	appendPopupWindow(first_window, new_window);

	return new_window;
}

static void appendPopupWindow(PopupWindow* base_window, PopupWindow* new_window)
{
	while(base_window->next != NULL)
	{
		base_window = base_window->next;
	}
	base_window->next = new_window;
	new_window->prev = base_window;
}

void removePopupWindow(PopupWindow* old_window)
{
	old_window->prev->next = old_window->next;
	if (old_window->next != NULL)
	{
		old_window->next->prev = old_window->prev;
	}
	free(old_window);
}
