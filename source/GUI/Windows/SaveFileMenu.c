#include "SaveFileMenu.h"

static int file_num = 0;
static char file_names[BUF_SIZE][BUF_SIZE];
static int active = -1;
void drawSaveFileMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Save File", nk_rect(50, 50, 300, 500),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
		NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		if (file_num == 0)
		{
			DirPtr* dirPtr = newDirPtr();
			char tmp_str[BUF_SIZE] = "";
			snprintf(tmp_str, BUF_SIZE, "%s\\saves", platform->app_dir_path);
			if (openDir(dirPtr, tmp_str)) 
			{
				printf("Failed to open directory\n");
				return;
			}
			while (getNextFile(dirPtr, file_names[file_num++]) == 0); // Loads all file names
			file_num--;
			if (closeDir(dirPtr))
			{
				printf("Failed to close directory\n");
				file_num = 0;
				return;
			}
		}

		for (int i = 0; i < file_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 200, 1);
			active = nk_option_label_align(platform->ctx, file_names[i], active == i, NK_WIDGET_LEFT, NK_TEXT_LEFT) ? i : active;
		}

		nk_layout_row_static(platform->ctx, 30, 200, 1);
		active = nk_option_label_align(platform->ctx, "New save file:", active == file_num, NK_WIDGET_LEFT, NK_TEXT_LEFT) ? file_num : active;
		nk_layout_row_static(platform->ctx, 30, 200, 1);
		nk_edit_string_zero_terminated(platform->ctx, NK_EDIT_SIMPLE, file_names[file_num], BUF_SIZE, nk_filter_default);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		if (nk_button_label(platform->ctx, "Save File") && active >= 0)
		{
			if(saveAppState(platform->current_app_state, platform->app_dir_path, file_names[active]))
			{
				printf("\nSave did not work\n");
			}
			else
			{
				platform->flags &= ~AP_FLAG_SAVE_STATE;
				file_num = 0;
				active = -1;
			}
		}
		if (nk_button_label(platform->ctx, "Back"))
		{
			platform->flags &= ~AP_FLAG_SAVE_STATE;
			file_num = 0;
			active = -1;
		}
	}
	nk_end(platform->ctx);
}