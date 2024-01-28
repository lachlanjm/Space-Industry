#include "FactoryMenu.h"

void drawFactoryMenu(AppPlatform* platform, Factory* factory, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Factory", nk_rect(50, 50, 450, 300),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Location:", NK_TEXT_LEFT);
		if (nk_button_label(platform->ctx, getNameTransportNode(factory->location)))
		{
			addNewPopupWindow(platform->first_window, LOCATION_MENU, &factory->location);
		}

		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Production Recipe:", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProductionRecipe(factory->productionRecipe), NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 30, 200, 2);
		nk_label(platform->ctx, "Processing speed:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u", factory->processing_speed);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

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
				addNewPopupWindow(platform->first_window, STOCKPILE_MENU, &factory->stockpiles_in[i]);
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
				addNewPopupWindow(platform->first_window, STOCKPILE_MENU, &factory->stockpiles_out[i]);
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
				addNewPopupWindow(platform->first_window, ORDER_MENU, &factory->orders_in[i]);
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
				addNewPopupWindow(platform->first_window, ORDER_MENU, &factory->orders_out[i]);
			}
		}
	}
	nk_end(platform->ctx);
}