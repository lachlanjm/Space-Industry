#include "LogisticsContractMenu.h"

void drawLogisticsContractMenu(AppPlatform* platform, LogisticsContract* logisticsContract, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Logistics Contract", nk_rect(50, 50, 250, 250),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Vehicle: ", NK_TEXT_LEFT);
		if (nk_button_label(platform->ctx, "Show"))
		{
			addNewPopupWindow(platform->first_window, VEHICLE, logisticsContract->assigned_vehicle);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Selling factory: ", NK_TEXT_LEFT);
		if (nk_button_label(platform->ctx, "Show"))
		{
			addNewPopupWindow(platform->first_window, FACTORY, logisticsContract->selling_factory);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Buying Factory: ", NK_TEXT_LEFT);
		if (nk_button_label(platform->ctx, "Show"))
		{
			addNewPopupWindow(platform->first_window, FACTORY, logisticsContract->buying_factory);
		}

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Contract Phase: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", logisticsContract->current_phase);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Product: ", NK_TEXT_LEFT);
		nk_label(platform->ctx, getNameProduct(logisticsContract->product), NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Quantity: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%d", logisticsContract->quantity);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);
	}
	nk_end(platform->ctx);
}