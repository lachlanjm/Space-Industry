#include "LogisticsManagerMenu.h"

void drawLogisticsManagerMenu(AppPlatform* platform, LogisticsManager* logisticsManager, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Logistics Manager", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Contracts: ", NK_TEXT_LEFT);

		for (int i = 0; i < logisticsManager->contracts_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Show contract"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, LOGISTICS_CONTRACT_MENU, &logisticsManager->contracts[i]);
			}
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Vehicles: ", NK_TEXT_LEFT);

		for (int i = 0; i < logisticsManager->vehicles_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Show vehicle"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, VEHICLE_MENU, logisticsManager->vehicles[i]);
			}
		}
	}
	nk_end(platform->ctx);
}