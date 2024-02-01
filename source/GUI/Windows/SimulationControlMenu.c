#include "SimulationControlMenu.h"

void drawSimulationControlMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Simulation Control", nk_rect(50, 50, 100, 70),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE))
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

