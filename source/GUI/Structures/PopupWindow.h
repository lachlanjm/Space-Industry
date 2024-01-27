#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

typedef struct PopupWindow PopupWindow;

#include "..\Windows\FactoryList.h"
#include "..\Windows\FactoryMenu.h"
#include "..\Windows\LocationGroup.h"
#include "..\Windows\LocationMenu.h"
#include "..\Windows\MainMenu.h"
#include "..\Windows\OrderMenu.h"
#include "..\Windows\StockpileMenu.h"
#include "..\Windows\VehicleMenu.h"
#include "..\Enums\WindowTypes.h"

#define BUF_SIZE 64

typedef struct PopupWindow {
	WindowTypes window_type;
	char name[BUF_SIZE];

	void* struct_ptr;

	PopupWindow* next;
	PopupWindow* prev;
} PopupWindow;

void assignPopupWindowValues(PopupWindow* window, WindowTypes window_type, void* struct_ptr);
void drawPopupWindow(PopupWindow* window, AppPlatform* platform);
PopupWindow* addNewPopupWindow(PopupWindow* first_window, WindowTypes window_type, void* struct_ptr);
void removePopupWindow(PopupWindow* old_window);


#endif