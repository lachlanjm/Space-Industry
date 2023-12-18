#include "Order.h"

Order* newOrder(const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
    Order* order = (Order*) malloc(1 * sizeof(Order));

    order->offering_factory = offering_factory;
    order->offer_num = offer_num;
    order->price = price;

    order->left_order = NULL;
    order->right_order = NULL;

    return order;
}

void assignOrderValues(Order* order, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price, const Order* prev_order, const Order* left_order, const Order* right_order)
{
    order->offering_factory = offering_factory;
    order->offer_num = offer_num;
    order->price = price;

    order->prev_order = prev_order;
    order->left_order = left_order;
    order->right_order = right_order;
}

// DONT CLEAN CONSTITUENT
void clean(Order* order)
{
    if (order->left_order != NULL) {
        clean(order->left_order);
        free(order->left_order);
        order->left_order = NULL;
    }
    if (order->right_order != NULL) {
        clean(order->right_order);
        free(order->right_order);
        order->right_order = NULL;
    }
}
