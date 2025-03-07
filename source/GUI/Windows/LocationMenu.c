#include "LocationMenu.h"

void drawLocationMenu(AppPlatform* platform, TransportNode location, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Location", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Location: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameTransportNode(location), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Controlling Government"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, GOVERNMENT_MENU, getGovernmentByLocation(location));
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Local Population"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, LOCAL_POPULATION_MENU, getLocalPopulationByLocation(location));
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Product Markets"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, LOCAL_PRODUCT_MARKET_LIST, &location);
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
					const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
					const struct nk_vec2 size = nk_window_get_size(platform->ctx);
					setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
					addNewPopupWindow(platform, LOCATION_MENU, (TransportNode*) &i);
				}
			}
		}
	}
	nk_end(platform->ctx);
}