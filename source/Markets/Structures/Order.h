#ifndef ORDER_H
#define ORDER_H

#include "..\..\Production\Structures\Factory.h"
#include "..\..\Production\Structures\Stockpile.h"

#include <stdint.h>

typedef struct Order {
    Factory* offering_factory;
    QUANTITY_INT offer_num;
    uint_fast16_t price;

    Order* prev_order;
    Order* left_order;
    Order* right_order;
} Order;

Order* newOrder(const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);
void assignOrderValues(Order* order, const Factory* offering_factory, const QUANTITY_INT offer_num, 
    const uint_fast16_t price, const Order* prev_order, const Order* left_order, const Order* right_order);


// DONT CLEAN CONSTITUENT
void cleanOrder(Order* order);

#endif