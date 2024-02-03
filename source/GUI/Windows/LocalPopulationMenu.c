#include "LocalPopulationMenu.h"

void drawLocalPopulationMenu(AppPlatform* platform, LocalPopulation* population, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Local Population List", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Population: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", population->population_number);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Population Centre"))
		{
			addNewPopupWindow(platform->first_window, FACTORY_MENU, &population->population_centre);
		}
	}
	nk_end(platform->ctx);
}
