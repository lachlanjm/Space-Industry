#include "LogisticsManagerMenu.h"

void drawLogisticsManagerMenu(AppPlatform* platform, LogisticsManager* logisticsManager, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Logistics Manager", nk_rect(50, 50, 250, 250),
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
				addNewPopupWindow(platform->first_window, LOGISTICS_CONTRACT_MENU, &logisticsManager->contracts[i]);
			}
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Vehicles: ", NK_TEXT_LEFT);

		for (int i = 0; i < logisticsManager->vehicles_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Show vehicle"))
			{
				addNewPopupWindow(platform->first_window, VEHICLE_MENU, &logisticsManager->vehicles[i]);
			}
		}
	}
	nk_end(platform->ctx);
}