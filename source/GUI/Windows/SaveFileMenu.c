#include "SaveFileMenu.h"

void drawSaveFileMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Save File", nk_rect(50, 50, 130, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Save"))
		{
			if(saveAppState(platform->current_app_state, platform->app_dir_path, "my_second_save"))
			{
				printf("\nSave did not work\n");
			}
			else
			{
				platform->flags &= ~AP_FLAG_SAVE_STATE;
			}
		}
	}
	nk_end(platform->ctx);
}