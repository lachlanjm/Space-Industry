#include "GlobalProductMarketMenu.h"

void drawGlobalProductMarketMenu(AppPlatform* const platform, const Product product, const char* const name)
{
	if (nk_begin_titled(platform->ctx, name, "Global Product Market", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";
		HISTORY_INT history_value;
		HistoryIterator* hist_iter;

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Product: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProduct(product), NK_TEXT_LEFT);

		const HistoryWtdAvgArray* const buy_hist = getMarketBuyHistoryWtdAvgArrByProduct(product);
		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Average Buy Price: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%u", getAvgHistoryWtdAvgArray(buy_hist));
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(buy_hist, HISTORY_WTD_AVG_ARRAY_AVG_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinAvgHistoryWtdAvgArray(buy_hist));
			const float max = MAX(0, getMaxAvgHistoryWtdAvgArray(buy_hist));
			if ( nk_chart_begin(platform->ctx, NK_CHART_LINES, MAX_HISTORY + 1, min, max) )
			{
				while (getNextHistoryIterItem(hist_iter, &history_value)) 
				{
					nk_chart_push(platform->ctx, (float) history_value);
				};
				nk_chart_end(platform->ctx);
			};
			closeHistoryIterator(hist_iter);
		}
		
		const HistoryWtdAvgArray* const sell_hist = getMarketSellHistoryWtdAvgArrByProduct(product);
		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Average Sell Price: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%u", getAvgHistoryWtdAvgArray(sell_hist));
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(sell_hist, HISTORY_WTD_AVG_ARRAY_AVG_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinAvgHistoryWtdAvgArray(sell_hist));
			const float max = MAX(0, getMaxAvgHistoryWtdAvgArray(sell_hist));
			if ( nk_chart_begin(platform->ctx, NK_CHART_LINES, MAX_HISTORY + 1, min, max) )
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