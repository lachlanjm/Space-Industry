#include "PopupWindow.h"

static void appendPopupWindow(PopupWindow* base_window, PopupWindow* new_window);

void assignPopupWindowValues(PopupWindow* window, WindowTypes window_type, void* struct_ptr)
{
	window->window_type = window_type;
    snprintf(window->name, BUF_SIZE, "%p", struct_ptr);
	window->struct_ptr = struct_ptr;
	window->next = NULL;
	window->prev = NULL;
}

void drawPopupWindow(PopupWindow* window, AppPlatform* platform)
{
	//if (nk_window_is_closed(platform->ctx, window->name)) removePopupWindow(window);
	switch (window->window_type)
	{
	case MAIN_MENU:
		drawMainMenu(platform, (AppState*)window->struct_ptr, window->name);
		break;
	case FACTORY:
		drawFactoryMenu(platform, (Factory*)window->struct_ptr, window->name);
		break;
	
	default:
		break;
	}
}

PopupWindow* addNewPopupWindow(PopupWindow* first_window, WindowTypes window_type, void* struct_ptr)
{
	PopupWindow* new_window = calloc(1, sizeof(PopupWindow));

	assignPopupWindowValues(new_window, window_type, struct_ptr);
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
	while (old_window->next != NULL)
	{
		old_window->next->prev = old_window->prev;
	}
	free(old_window);
}
