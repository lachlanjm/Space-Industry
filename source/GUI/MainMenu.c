#include "MainMenu.h"

void drawBaseMenu(AppPlatform* platform)
{
    if (nk_begin(platform->ctx, "Main Menu", nk_rect(50, 50, 230, 250),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        
    }
    nk_end(platform->ctx);
}