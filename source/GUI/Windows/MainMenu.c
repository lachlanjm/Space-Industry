#include "MainMenu.h"

void drawMainMenu(AppPlatform* platform, AppState* current_app_state, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Main Menu", nk_rect(50, 50, 130, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Companies"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, COMPANY_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Governments"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, GOVERNMENT_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Global Markets"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, GLOBAL_PRODUCT_MARKET_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Map"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, LOCATION_GROUP, current_app_state);
		}
			
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Logistics"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, LOGISTICS_MANAGER_LIST, current_app_state);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Populations"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, LOCAL_POPULATION_LIST, current_app_state);
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