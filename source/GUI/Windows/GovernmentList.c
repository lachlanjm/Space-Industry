#include "GovernmentList.h"

void drawGovernmentList(AppPlatform* const platform, AppState* const current_app_state, const char* const name)
{
	if (nk_begin_titled(platform->ctx, name, "Government List", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Governments:", NK_TEXT_LEFT);

		for (int i = 0; i < getGovernmentNum(); i++)
		{
			nk_layout_row_static(platform->ctx, 30, 200, 2);
			snprintf(buffer, BUF_SIZE, "Government #%i", getGovernmentByIndex(i)->id);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, GOVERNMENT_MENU, getGovernmentByIndex(i));
			}
		}
		
	}
	nk_end(platform->ctx);
}