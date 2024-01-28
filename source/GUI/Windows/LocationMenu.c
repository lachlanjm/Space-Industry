#include "LocationMenu.h"

void drawLocationMenu(AppPlatform* platform, TransportNode location, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Location", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Location: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameTransportNode(location), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Product Markets"))
		{
			addNewPopupWindow(platform->first_window, PRODUCT_MARKET_LIST, &location);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Connections: ", NK_TEXT_LEFT);
		for (int i = 0; i < TRANSPORT_NODE_COUNT; i++)
		{
			if (getConnectionType(location, (TransportNode) i) != NOTHING)
			{
				nk_layout_row_static(platform->ctx, 30, 100, 1);
				if (nk_button_label(platform->ctx, getNameTransportNode((TransportNode) i)))
				{
					addNewPopupWindow(platform->first_window, LOCATION_MENU, (TransportNode*) &i);
				}
			}
		}
	}
	nk_end(platform->ctx);
}