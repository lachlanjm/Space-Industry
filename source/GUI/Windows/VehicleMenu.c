#include "VehicleMenu.h"

void drawVehicleMenu(AppPlatform* platform, Vehicle* vehicle, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Vehicle", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Current Location: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameTransportNode(vehicle->current_location), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Distance past current: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u", vehicle->distance_travelled);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Target Location: ", NK_TEXT_LEFT);
		if (vehicle->end_location == -1)
		{
			nk_label(platform->ctx, "No end location", NK_TEXT_LEFT);
		}
		else
		{
			nk_label(platform->ctx, getNameTransportNode(vehicle->end_location), NK_TEXT_LEFT);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Max capacity: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u", vehicle->max_capacity);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Stockpile"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, STOCKPILE_MENU, &vehicle->stockpile);
		}

		nk_layout_row_static(platform->ctx, 30, 150, 1);
		if (vehicle->end_factory != NULL)
		{
			if (nk_button_label(platform->ctx, "End Factory"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, FACTORY_MENU, vehicle->end_factory);
			}
		}
		else
		{
			nk_label(platform->ctx, "No end factory", NK_TEXT_LEFT);
		}
	}
	nk_end(platform->ctx);
}