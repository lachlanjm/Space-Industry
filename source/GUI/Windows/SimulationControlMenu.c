#include "SimulationControlMenu.h"

void drawSimulationControlMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Controls", nk_rect(WINDOW_WIDTH - 120, 0, 120, 85),
		NK_WINDOW_BORDER|NK_WINDOW_TITLE))
	{
		nk_layout_row_static(platform->ctx, 30, 30, 2);
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_CIRCLE_SOLID))
		{
			platform->flags &= ~AP_FLAG_RUN_SIMULATION;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_TRIANGLE_RIGHT))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
		}
	}
	nk_end(platform->ctx);
}

