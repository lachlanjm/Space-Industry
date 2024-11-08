#include "StockpileMenu.h"

static HistoryIterator* hist_iter;
static HISTORY_INT history_value;
void drawStockpileMenu(AppPlatform* platform, Stockpile* stockpile, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Stockpile", nk_rect(50, 50, 250, 150),
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

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Change:", NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(&stockpile->quantity_history, HISTORY_ARRAY_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinValueHistoryArray(&stockpile->quantity_history));
			const float max = MAX(0, getMaxValueHistoryArray(&stockpile->quantity_history));
			if ( nk_chart_begin(platform->ctx, NK_CHART_LINES, MAX_HISTORY + 1, min, max) ) // TODO: SET MIN MAX TO HIST MIN MAX
			{
				while (getNextHistoryIterItem(hist_iter, &history_value)) 
				{
					nk_chart_push(platform->ctx, (float) history_value);
				};
				nk_chart_end(platform->ctx);
			};
			closeHistoryIterator(hist_iter);
		}
	}
	nk_end(platform->ctx);
}