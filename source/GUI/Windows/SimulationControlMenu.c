#include "SimulationControlMenu.h"

void drawSimulationControlMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Controls", nk_rect(WINDOW_WIDTH - 300, 0, 300, 85),
		NK_WINDOW_BORDER|NK_WINDOW_TITLE))
	{
		nk_layout_row_static(platform->ctx, 30, 30, 7);
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_RECT_SOLID))
		{
			platform->flags &= ~AP_FLAG_RUN_SIMULATION;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_CIRCLE_SOLID))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
			platform->tick_time = AP_VERY_SLOW;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_TRIANGLE_LEFT))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
			platform->tick_time = AP_SLOW;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_MINUS))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
			platform->tick_time = AP_NORMAL;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_PLUS))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
			platform->tick_time = AP_FAST;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_TRIANGLE_RIGHT))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
			platform->tick_time = AP_VERY_FAST;
		}
		if (nk_button_symbol(platform->ctx, NK_SYMBOL_TRIANGLE_UP))
		{
			platform->flags |= AP_FLAG_RUN_SIMULATION;
			platform->tick_time = AP_MAX;
		}
	}
	nk_end(platform->ctx);
}

