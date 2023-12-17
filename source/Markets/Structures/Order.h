#ifndef ORDER_H
#define ORDER_H

#include "..\..\Production\Structures\Factory.h"
#include "..\..\Production\Structures\Stockpile.h"

#include <stdint.h>

typedef struct Order {
    Factory* offering_factory;
    QUANTITY_INT offer_num;
    uint_fast16_t price;

    Order* left_order;
    Order* right_order;
} Order;

Order* newOrder(const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);
void assignOrderValues(Order* order, const Factory* offering_factory, const QUANTITY_INT offer_num, 
    const uint_fast16_t price, const Order* left_order, const Order* right_order);
inline void swapOrders(Order* order1, Order* order2);

// For sale orders
void pushUpOrder(Order* base_order, Order* new_order);

// For buy orders
void pushDownOrder(Order* base_order, Order* new_order);

// DONT CLEAN CONSTITUENT
void clean(Order* order);

#endif