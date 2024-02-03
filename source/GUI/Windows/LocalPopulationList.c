#include "LocalPopulationList.h"

void drawLocalPopulationList(AppPlatform* platform, AppState* current_app_state, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Local Population List", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 150, 1);
		nk_label(platform->ctx, "Local Populations: ", NK_TEXT_LEFT);

		for (int i = 0; i < current_app_state->local_population_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Local Population"))
			{
				addNewPopupWindow(platform->first_window, LOCAL_POPULATION_MENU, &current_app_state->local_population[i]);
			}
		}
	}
	nk_end(platform->ctx);
}
