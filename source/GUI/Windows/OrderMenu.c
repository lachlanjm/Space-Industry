#include "OrderMenu.h"

void drawOrderMenu(AppPlatform* platform, Order* order, char* name)
{
	if (nk_begin_titled(platform->ctx, name, "Order", 
		nk_rect(platform->new_win_info.child_x, platform->new_win_info.child_y,
			platform->new_win_info.child_w, platform->new_win_info.child_h),
		NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE
		|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
	{
		char buffer[BUF_SIZE] = "";

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Quantity: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "%u", order->offer_num);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 2);
		nk_label(platform->ctx, "Price: ", NK_TEXT_LEFT);
		snprintf(buffer, BUF_SIZE, "$%u", order->price);
		nk_label(platform->ctx, buffer, NK_TEXT_LEFT);

		nk_layout_row_static(platform->ctx, 30, 100, 1);
		if (nk_button_label(platform->ctx, "Offering factory"))
		{
			const struct nk_vec2 pos = nk_window_get_position(platform->ctx);
			const struct nk_vec2 size = nk_window_get_size(platform->ctx);
			setParentDimensions(platform, pos.x, pos.y, size.x, size.y);
			addNewPopupWindow(platform, FACTORY_MENU, order->offering_factory);
		}
	}
	nk_end(platform->ctx);
}