#include "LocalPopulationMenu.h"

void drawLocalPopulationMenu(AppPlatform* platform, LocalPopulation* population, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Local Population Menu", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Population: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", population->population_number);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Employed Pop.: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", population->employed_number);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Unemployed Pop.: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", population->population_number - population->employed_number);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Government"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, GOVERNMENT_MENU, getGovernmentByLocation(population->population_centre.location));
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Population Centre"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, FACTORY_MENU, &population->population_centre);
		}
	}
	nk_end(platform->ctx);
}
