#include "FactoryMenu.h"

void drawFactoryMenu(AppPlatform* platform, Factory* factory, char* name)
{
    if (nk_begin_titled(platform->ctx, name, "Factory", nk_rect(50, 50, 400, 250),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
        |NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
		char buffer[BUF_SIZE] = "";
		nk_layout_row_static(platform->ctx, 30, 200, 2);
        nk_label(platform->ctx, "Production Recipe:", NK_TEXT_LEFT);
        nk_label(platform->ctx, getNameProductionRecipe(factory->productionRecipe), NK_TEXT_LEFT);
		
		nk_layout_row_static(platform->ctx, 30, 200, 2);
        nk_label(platform->ctx, "Processing speed:", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", factory->processing_speed);
        nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
        nk_label(platform->ctx, "Inputs:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_in_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 150, 2);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_in[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%d", factory->stockpiles_in[i].quantity);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
        nk_label(platform->ctx, "Outputs:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_out_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 150, 2);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_out[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%d", factory->stockpiles_out[i].quantity);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
		}
		
		nk_layout_row_static(platform->ctx, 30, 200, 2);
        nk_label(platform->ctx, "Location:", NK_TEXT_LEFT);
        nk_label(platform->ctx, getNameTransportNode(factory->location), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
        nk_label(platform->ctx, "Orders in:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_in_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 150, 4);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_in[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%d x", factory->orders_in[i].offer_num);
			nk_label(platform->ctx, buffer, NK_TEXT_RIGHT);
			snprintf(buffer, BUF_SIZE, "$%d", factory->orders_in[i].price);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				addNewPopupWindow(platform->first_window, ORDER, &factory->orders_in[i]);
			}
		}

		nk_layout_row_static(platform->ctx, 30, 100, 1);
        nk_label(platform->ctx, "Orders out:", NK_TEXT_LEFT);

		for (int i = 0; i < factory->stockpiles_out_num; i++)
		{
			nk_layout_row_static(platform->ctx, 30, 150, 4);
			nk_label(platform->ctx, getNameProduct(factory->stockpiles_out[i].product_type), NK_TEXT_LEFT);
			snprintf(buffer, BUF_SIZE, "%d x", factory->orders_out[i].offer_num);
			nk_label(platform->ctx, buffer, NK_TEXT_RIGHT);
			snprintf(buffer, BUF_SIZE, "$%d", factory->orders_out[i].price);
			nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
			if (nk_button_label(platform->ctx, "Show"))
			{
				addNewPopupWindow(platform->first_window, ORDER, &factory->orders_out[i]);
			}
		}
    }
    nk_end(platform->ctx);
}