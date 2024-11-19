#include "ProductMarketMenu.h"

void drawProductMarketMenu(AppPlatform* platform, ProductMarket* productMarket, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Product Market", nk_rect(50, 50, 350, 350),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";
		HISTORY_INT history_value;
		HistoryIterator* hist_iter;

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Product: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProduct(productMarket->product_type), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Average Buy Price: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%u", getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array));
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(&productMarket->buy_hist_array, HISTORY_WTD_AVG_ARRAY_AVG_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinAvgHistoryWtdAvgArray(&productMarket->buy_hist_array));
			const float max = MAX(0, getMaxAvgHistoryWtdAvgArray(&productMarket->buy_hist_array));
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

		nk_layout_row_static(platform->ctx, 30, 150, 2);
		nk_label(platform->ctx, "Average Sell Price: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%u", getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array));
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(&productMarket->sell_hist_array, HISTORY_WTD_AVG_ARRAY_AVG_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinAvgHistoryWtdAvgArray(&productMarket->sell_hist_array));
			const float max = MAX(0, getMaxAvgHistoryWtdAvgArray(&productMarket->sell_hist_array));
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

		if (productMarket->buy_order_arr_size > 0)
		{
			nk_layout_row_static(platform->ctx, 30, 150, 1);
			if (nk_button_label(platform->ctx, "Highest Buy Order"))
			{
				addNewPopupWindow(platform->first_window, ORDER_MENU, productMarket->buy_order_arr[0]);
			}
		}
		if (productMarket->sell_order_arr_size > 0)
		{
			nk_layout_row_static(platform->ctx, 30, 150, 1);
			if (nk_button_label(platform->ctx, "Lowest Sell Order"))
			{
				addNewPopupWindow(platform->first_window, ORDER_MENU, productMarket->sell_order_arr[0]);
			}
		}
	}
	nk_end(platform->ctx);
}