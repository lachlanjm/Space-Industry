#include "LoadFileMenu.h"

void drawLoadFileMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Load File", nk_rect(50, 50, 130, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Load"))
		{
			if (platform->current_app_state) 
			{
				cleanAppState(platform->current_app_state);
				free(platform->current_app_state);
			}
			platform->current_app_state = loadAppState(platform->app_dir_path, "my_first_save");
			if (platform->current_app_state)
			{
				resetPlatform(platform);
				platform->flags &= ~AP_FLAG_LOAD_FILE;
			}
		}
	}
	nk_end(platform->ctx);
}
