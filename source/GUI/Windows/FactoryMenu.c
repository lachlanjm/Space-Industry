#include "FactoryMenu.h"

static HistoryIterator* hist_iter;
static HISTORY_INT history_value;
void drawFactoryMenu(AppPlatform* platform, Factory* factory, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Factory", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Location:", NK_TEXT_LEFT);
		if (nk_button_label(platform->ctx, getNameTransportNode(factory->location)))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, LOCATION_MENU, &factory->location);
		}

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Production Recipe:", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProductionRecipe(factory->productionRecipe), NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Processing speed:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u", factory->processing_speed);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Employee wages:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%u", factory->employee_wages);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Employees:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u / %u", factory->current_employee_num, factory->max_employee_num);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT); 

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Profit:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%Lf", getAvgHistoryArrayAvg(&factory->profit_history));
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 100, 300, 1);
		hist_iter = newHistoryIterator(&factory->profit_history, HISTORY_ARRAY_AVG_TYPE);
		if (hist_iter)
		{
			const float min = MIN(0, getMinValueHistoryArrayAvg(&factory->profit_history));
			const float max = MAX(0, getMaxValueHistoryArrayAvg(&factory->profit_history));
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

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Inputs:", NK_TEXT_LEFT);
		
		for (int i = 0; i < factory->stockpiles_in_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 3);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_in[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "x %u", factory->stockpiles_in[i].quantity);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, STOCKPILE_MENU, &factory->stockpiles_in[i]);
			}
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Outputs:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_out_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 3);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_out[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%u", factory->stockpiles_out[i].quantity);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, STOCKPILE_MENU, &factory->stockpiles_out[i]);
			}
		}
		
		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Orders in:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_in_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 4);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_in[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%u (%u) x", factory->orders_in[i].offer_num, factory->ordered_in[i]);
			nk_label(platform->ctx, buffer, NK_TEXT_RIGHT);
			snprintf(buffer, BUF_SIZE, "$%u", factory->orders_in[i].price);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, ORDER_MENU, &factory->orders_in[i]);
			}
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		nk_label(platform->ctx, "Orders out:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_out_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 100, 4);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_out[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%u (%u) x", factory->orders_out[i].offer_num, factory->ordered_out[i]);
			nk_label(platform->ctx, buffer, NK_TEXT_RIGHT);
			snprintf(buffer, BUF_SIZE, "$%u", factory->orders_out[i].price);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
				const struct nk_vec2 size = nk_window_get_size(platform->ctx);
				setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
				addNewPopupWindow(platform, ORDER_MENU, &factory->orders_out[i]);
			}
		}
	}
	nk_end(platform->ctx);
}