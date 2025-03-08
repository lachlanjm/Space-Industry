#include "GovernmentMenu.h"

void drawGovernmentMenu(AppPlatform* const platform, Government* const government, const char* const name)
{
	if (nk_begin_titled(platform->ctx, name, "Government", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";
		HISTORY_INT history_value;
		HistoryIterator* hist_iter;

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Wealth:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%i", government->wealth);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "GST Rate:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%.3f%%", (float)government->gst_rate / 1000.0f);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Government Markets"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, GOVERNMENT_MARKET_MENU, government);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Consumption:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%.0Lf", getAvgHistoryArrayAvg(&government->consumption));
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(&government->consumption, HISTORY_ARRAY_AVG_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinValueHistoryArrayAvg(&government->consumption));
			const float max = MAX(0, getMaxValueHistoryArrayAvg(&government->consumption));
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
		
		nk_layout_row_static(platform->ctx, 30, 100, 3);
		nk_label(platform->ctx, "Tariffs", NK_TEXT_LEFT);
		nk_label(platform->ctx, "Import:", NK_TEXT_LEFT);
		nk_label(platform->ctx, "Export:", NK_TEXT_LEFT);

		const int gov_num = getGovernmentNum();
		for (int i = 0; i < gov_num; i++)
		{
			const Government* const other_gov = getGovernmentByIndex(i);
			if (other_gov == government) continue;

			nk_layout_row_static(platform->ctx, 30, 100, 3);
			if (nk_button_label(platform->ctx, "Government"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, GOVERNMENT_MENU, other_gov);
			}
			
			snprintf(buffer, BUF_SIZE, "%.3f%%", (float)government->import_tariffs[i] / 1000.0f);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

			snprintf(buffer, BUF_SIZE, "%.3f%%", (float)government->export_tariffs[i] / 1000.0f);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		}
	}
	nk_end(platform->ctx);
}