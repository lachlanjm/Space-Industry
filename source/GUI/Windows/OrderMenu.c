#include "OrderMenu.h"

void drawOrderMenu(AppPlatform* platform, Order* order, char* name)
{
    if (nk_begin_titled(platform->ctx, name, "Order", nk_rect(50, 50, 200, 250),
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
            addNewPopupWindow(platform->first_window, FACTORY, order->offering_factory);
        }
    }
    nk_end(platform->ctx);
}