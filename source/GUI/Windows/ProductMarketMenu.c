#include "ProductMarketMenu.h"

void drawProductMarketMenu(AppPlatform* platform, ProductMarket* productMarket, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Product Market", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		// char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Product: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProduct(productMarket->product_type), NK_TEXT_LEFT);

		if (productMarket->highest_buy_order)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Highest Buy Order"))
			{
				addNewPopupWindow(platform->first_window, ORDER_MENU, productMarket->highest_buy_order);
			}
		}
		if (productMarket->lowest_sell_order)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			if (nk_button_label(platform->ctx, "Lowest Sell Order"))
			{
				addNewPopupWindow(platform->first_window, ORDER_MENU, productMarket->lowest_sell_order);
			}
		}
	}
	nk_end(platform->ctx);
}