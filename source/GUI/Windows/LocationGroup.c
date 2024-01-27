#include "LocationGroup.h"

void drawLocationGroup(AppPlatform* platform, AppState* current_app_state, char* name)
{
    if (nk_begin_titled(platform->ctx, name, "Location Group", nk_rect(50, 50, 400, 250),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
        |NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
		// char buffer[BUF_SIZE] = "";
    }
    nk_end(platform->ctx);
}