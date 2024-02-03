#include "MainMenu.h"

void drawMainMenu(AppPlatform* platform, AppState* current_app_state, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Main Menu", nk_rect(50, 50, 130, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Factories"))
		{
			addNewPopupWindow(platform->first_window, FACTORY_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Map"))
		{
			addNewPopupWindow(platform->first_window, LOCATION_GROUP, current_app_state);
		}
			
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Logistics"))
		{
			addNewPopupWindow(platform->first_window, LOGISTICS_MANAGER_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Populations"))
		{
			addNewPopupWindow(platform->first_window, LOCAL_POPULATION_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Load"))
		{
			platform->flags |= AP_FLAG_LOAD_FILE;
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Save"))
		{
			platform->flags |= AP_FLAG_SAVE_STATE;
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Quit"))
		{
			platform->flags |= AP_FLAG_CLOSE;
		}
	}
	nk_end(platform->ctx);
}