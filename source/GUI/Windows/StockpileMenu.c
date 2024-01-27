#include "StockpileMenu.h"

void drawStockpileMenu(AppPlatform* platform, Stockpile* stockpile, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Stockpile", nk_rect(50, 50, 200, 100),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Product: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProduct(stockpile->product_type), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Quantity: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u", stockpile->quantity);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
	}
	nk_end(platform->ctx);
}