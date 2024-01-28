#include "Order.h"

static ORDER_ID_INT id_next = 0;
Order* newOrder(const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
	Order* order = (Order*) malloc(1 * sizeof(Order));

	assignOrderValues(order, offering_factory, offer_num, price, NULL, NULL, NULL);

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

	order->id = id_next++;
}

// DONT CLEAN CONSTITUENT
void cleanOrder(Order* order)
{
	
}
