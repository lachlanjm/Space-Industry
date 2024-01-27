#include "LogisticsManagerList.h"

void drawLogisticsManagerList(AppPlatform* platform, AppState* current_app_state, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Logistics Manager List", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Logistics Managers: ", NK_TEXT_LEFT);

		for (int i = 0; i < current_app_state->logistics_managers_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Logistics Manager"))
			{
				addNewPopupWindow(platform->first_window, LOGISTICS_MANAGER_MENU, &current_app_state->logistics_managers[i]);
			}
		}
	}
	nk_end(platform->ctx);
}