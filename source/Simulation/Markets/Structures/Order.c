#include "Order.h"

static ORDER_ID_INT id_next = 0;
Order* newOrder(const Factory* offering_factory, const QUANTITY_INT offer_num, const ORDER_PRICE_INT price)
{
	Order* order = (Order*) malloc(1 * sizeof(Order));

	assignOrderValues(order, offering_factory, offer_num, price);

	return order;
}

void assignOrderValues(Order* order, const Factory* offering_factory, const QUANTITY_INT offer_num, const ORDER_PRICE_INT price)
{
	order->offering_factory = offering_factory;
	order->offer_num = offer_num;
	order->price = price;

	order->id = id_next++;
}

void assignLoadIdOrder(Order* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

// DONT CLEAN CONSTITUENT
void cleanOrder(Order* order)
{
	
}
