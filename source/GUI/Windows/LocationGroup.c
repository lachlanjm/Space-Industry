#include "LocationGroup.h"

void drawLocationGroup(AppPlatform* platform, AppState* current_app_state, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Location Group", nk_rect(50, 50, 120, 300),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		for (int i = 0; i < TRANSPORT_NODE_COUNT; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, getNameTransportNode((TransportNode) i)))
			{
				addNewPopupWindow(platform->first_window, LOCATION, (TransportNode*) &i);
			}
		}
	}
	nk_end(platform->ctx);
}