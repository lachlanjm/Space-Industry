#include "LoadFileMenu.h"

static int file_num = 0;
static char file_names[BUF_SIZE][BUF_SIZE];
static int active = -1;
void drawLoadFileMenu(AppPlatform* platform, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Load File", nk_rect(50, 50, 200, 300),
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

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Load") && active >= 0)
		{
			if (platform->current_app_state) 
			{
				cleanAppState(platform->current_app_state);
				free(platform->current_app_state);
				platform->current_app_state = NULL;
			}
			platform->current_app_state = loadAppState(platform->app_dir_path, file_names[active]);
			if (platform->current_app_state)
			{
				resetPlatform(platform);
				platform->flags &= ~AP_FLAG_LOAD_FILE;
				file_num = 0;
				active = -1;
			}
			else
			{
				printf("\nFailed to load save state\n");
			}
		}
		
		if (nk_button_label(platform->ctx, "Back"))
		{
			platform->flags &= ~AP_FLAG_LOAD_FILE;
			file_num = 0;
			active = -1;
		}
	}
	nk_end(platform->ctx);
}
