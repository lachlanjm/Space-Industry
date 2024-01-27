#include "MainMenu.h"

void drawMainMenu(AppPlatform* platform, AppState* current_app_state, char* name)
{
    if (nk_begin_titled(platform->ctx, name, "Main Menu", nk_rect(50, 50, 230, 250),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
		nk_layout_row_static(platform->ctx, 30, 100, 3);
        if (nk_button_label(platform->ctx, "Factories"))
            fprintf(stdout, "Factory pressed!\n");
		if (nk_button_label(platform->ctx, "Map"))
            fprintf(stdout, "Map pressed!\n");
		if (nk_button_label(platform->ctx, "Logistics"))
            fprintf(stdout, "Logistics pressed!\n");
    }
    nk_end(platform->ctx);
}