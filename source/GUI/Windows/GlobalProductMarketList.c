#include "GlobalProductMarketList.h"

void drawGlobalProductMarketList(AppPlatform* const platform, AppState* const current_app_state, const char* const name)
{
	if (nk_begin_titled(platform->ctx, name, "Global Product Market List", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Product Markets: ", NK_TEXT_LEFT);

		for (int i = 0; i < PRODUCT_COUNT; i++)
		{
			const Product prod = (Product) i;
			nk_layout_row_static(platform->ctx, 30, 100, 1);
			snprintf(buffer, BUF_SIZE, "%s", getNameProduct(prod)); // Work around hardware issue TODO
			if (nk_button_label(platform->ctx, buffer))
			{
				addNewPopupWindow(platform->first_window, GLOBAL_PRODUCT_MARKET_MENU, &prod);
			}
		}
	}
	nk_end(platform->ctx);
}