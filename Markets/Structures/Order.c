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

void assignOrderValues(Order* order, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price, const Order* left_order, const Order* right_order)
{
    order->offering_factory = offering_factory;
    order->offer_num = offer_num;
    order->price = price;

    order->left_order = left_order;
    order->right_order = right_order;
}

inline void swapOrders(Order* order1, Order* order2) 
{
    // Change where factroy points to!!!! TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    static Order temp; // Saves memory allocation time
    temp.price = order2->price;
    temp.offer_num = order2->offer_num;
    temp.offering_factory = order2->offering_factory;
    temp.left_order = order2->left_order;
    temp.right_order = order2->right_order;
    order2->price = order1->price;
    order2->offer_num = order1->offer_num;
    order2->offering_factory = order1->offering_factory;
    order2->left_order = order1->left_order;
    order2->right_order = order1->right_order;
    order1->price = temp.price;
    order1->offer_num = temp.offer_num;
    order1->offering_factory = temp.offering_factory;
    order1->left_order = temp.left_order;
    order1->right_order = temp.right_order;
}

void pushUpOrder(Order* base_order, Order* new_order)
{
    if (base_order->price > new_order->price)
    {
        swapOrders(base_order, new_order);
        pushUpOrder(base_order->left_order, new_order);
    }
    else if (base_order->left_order == NULL) 
    {
        base_order->left_order = new_order;
    }
    else if (base_order->right_order == NULL) 
    {
        base_order->right_order = new_order;
    }
    else if (base_order->left_order->price > new_order->price) 
    {
        new_order->left_order = base_order->left_order;
        base_order->left_order = new_order;
    }
    else if (base_order->right_order->price > new_order->price) 
    {
        new_order->right_order = base_order->right_order;
        base_order->right_order = new_order;
    }
    else 
    {
        pushUpOrder(base_order->left_order, new_order);
    }
}

void pushDownOrder(Order* base_order, Order* new_order)
{
    if (base_order->price < new_order->price)
    {
        swapOrders(base_order, new_order);
        pushDownOrder(base_order->left_order, new_order);
    }
    else if (base_order->left_order == NULL) 
    {
        base_order->left_order = new_order;
    }
    else if (base_order->right_order == NULL) 
    {
        base_order->right_order = new_order;
    }
    else if (base_order->left_order->price < new_order->price) 
    {
        new_order->left_order = base_order->left_order;
        base_order->left_order = new_order;
    }
    else if (base_order->right_order->price < new_order->price) 
    {
        new_order->right_order = base_order->right_order;
        base_order->right_order = new_order;
    }
    else 
    {
        pushDownOrder(base_order->left_order, new_order);
    }
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
