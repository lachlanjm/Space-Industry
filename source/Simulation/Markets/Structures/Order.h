#ifndef ORDER_H
#define ORDER_H

typedef struct OrderDef Order;

#define ORDER_ID_INT uint_least16_t
#define ORDER_PRICE_INT uint_fast32_t

#include "..\..\Production\Structures\Factory.h"

typedef struct OrderDef {
	Factory* offering_factory;
	QUANTITY_INT offer_num;
	uint_fast32_t price;

	ORDER_ID_INT id;
} Order;

#include "..\..\Production\Structures\Stockpile.h"

#include <stdint.h>

Order* newOrder(const Factory* offering_factory, const QUANTITY_INT offer_num, const ORDER_PRICE_INT price);
void assignOrderValues(Order* order, const Factory* offering_factory, const QUANTITY_INT offer_num, const ORDER_PRICE_INT price);
void assignLoadIdOrder(Order* obj, const int id);

// DONT CLEAN CONSTITUENT
void cleanOrder(Order* order);

#endif