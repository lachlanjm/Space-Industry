#include "ProductMarket.h"

inline ProductMarket* newProductMarket(const Product product_type)
{
    ProductMarket* productMarket = (ProductMarket*) malloc(1 * sizeof(ProductMarket));

    productMarket->product_type = product_type;
    productMarket->lowest_sell_order = NULL;
    productMarket->highest_buy_order = NULL;

    return productMarket;
}

inline void assignNewProductMarket(ProductMarket* productMarket, const Product product_type)
{
    productMarket->product_type = product_type;
    productMarket->lowest_sell_order = NULL;
    productMarket->highest_buy_order = NULL;
}

inline void addSellOrder(ProductMarket* productMarket, Order* new_order)
{
    pullUpBuyOrder(productMarket->lowest_sell_order, new_order);
}

inline Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
    Order* order = newOrder(offering_factory, offer_num, price);
    addSellOrder(productMarket, order);
    return order;
}

inline void addBuyOrder(ProductMarket* productMarket, Order* new_order)
{
    pushDownBuyOrder(productMarket->highest_buy_order, new_order);
}

inline Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
    Order* order = newOrder(offering_factory, offer_num, price);
    addBuyOrder(productMarket, order);
    return order;
}

inline void resetBuyOrder(ProductMarket* productMarket, Order* new_order)
{
    pullUpBuyOrder(productMarket, new_order);
    pushDownBuyOrder(productMarket, new_order);
}

inline void resetSellOrder(ProductMarket* productMarket, Order* new_order)
{
    pushDownSellOrder(productMarket, new_order);
    pullUpSellOrder(productMarket, new_order);
}

void pushDownBuyOrder(ProductMarket* productMarket, Order* new_order) 
{
    if (productMarket->highest_buy_order == NULL)
    {
        new_order->prev_order = NULL;
        productMarket->highest_buy_order = new_order;
    }
    else if (new_order->price > productMarket->highest_buy_order->price)
    {
        // new_order is highest
        new_order->prev_order = NULL;
        if (new_order->left_order == NULL)
        {
            new_order->left_order = productMarket->highest_buy_order;
            productMarket->highest_buy_order->prev_order = new_order;
        }
        else if (new_order->right_order == NULL)
        {
            new_order->right_order = productMarket->highest_buy_order;
            productMarket->highest_buy_order->prev_order = new_order;
        }
        else 
        {
            pushDownBuyOrderFurther(new_order, productMarket->highest_buy_order);
        }
        productMarket->highest_buy_order = new_order;
    }
    else
    {
        pushDownBuyOrderFurther(productMarket->highest_buy_order, new_order);
    }
}

/*
Never replace base_order, only children
Could change to iterative
*/
void pushDownBuyOrderFurther(Order* base_order, Order* new_order)
{
    if (base_order->left_order == NULL) 
    {
        base_order->left_order = new_order;
        new_order->prev_order = base_order;
    }
    else if (base_order->right_order == NULL)
    {
        base_order->right_order = new_order;
        new_order->prev_order = base_order;
    }
    else if (new_order->price > base_order->left_order->price)
    {
        Order* old_left = base_order->left_order;
        base_order->left_order = new_order;
        new_order->prev_order = base_order;
        pushDownBuyOrderFurther(new_order, old_left);
    }
    else if (new_order->price > base_order->right_order->price)
    {
        Order* old_right = base_order->right_order;
        base_order->right_order = new_order;
        new_order->prev_order = base_order;
        pushDownBuyOrderFurther(new_order, old_right);
    }
    else 
    {
        // Right cause why not? and heavy emphasis elswhere to add to left
        pushDownBuyOrderFurther(base_order->right_order, new_order);
    }
}

/*
Could change to iterative
*/
void pullUpBuyOrder(ProductMarket* productMarket, Order* new_order)
{
    if (new_order->prev_order == NULL)
    {
        // DO NOTHING (AT THE TOP)
    }
    else if (new_order->price > new_order->prev_order->price)
    {
        if (new_order->prev_order->prev_order == NULL)
        {
            productMarket->highest_buy_order = new_order;
        }
        Order* old_prev = new_order->prev_order;
        new_order->prev_order = new_order->prev_order->prev_order;
        if (old_prev->left_order == new_order)
        {
            old_prev->left_order = NULL;
        }
        else if (old_prev->right_order == new_order)
        {
            old_prev->right_order = NULL;
        }
        else 
        {
            // ERROR!!!!!!!
        }
        old_prev->prev_order = NULL;
        pushDownBuyOrderFurther(new_order, old_prev);
        pullUpBuyOrder(productMarket, new_order);
    }
}


void pullUpSellOrder(ProductMarket* productMarket, Order* new_order)
{
    if (productMarket->lowest_sell_order == NULL)
    {
        new_order->prev_order = NULL;
        productMarket->lowest_sell_order = new_order;
    }
    else if (new_order->price < productMarket->lowest_sell_order->price)
    {
        // new_order is highest
        new_order->prev_order = NULL;
        if (new_order->left_order == NULL)
        {
            new_order->left_order = productMarket->lowest_sell_order;
            productMarket->lowest_sell_order->prev_order = new_order;
        }
        else if (new_order->right_order == NULL)
        {
            new_order->right_order = productMarket->lowest_sell_order;
            productMarket->lowest_sell_order->prev_order = new_order;
        }
        else 
        {
            pullUpSellOrderFurther(new_order, productMarket->lowest_sell_order);
        }
        productMarket->lowest_sell_order = new_order;
    }
    else
    {
        pullUpSellOrderFurther(productMarket->lowest_sell_order, new_order);
    }
}

/*
Never replace base_order, only children
Could change to iterative
*/
void pullUpSellOrderFurther(Order* base_order, Order* new_order)
{
    if (base_order->left_order == NULL) 
    {
        base_order->left_order = new_order;
        new_order->prev_order = base_order;
    }
    else if (base_order->right_order == NULL)
    {
        base_order->right_order = new_order;
        new_order->prev_order = base_order;
    }
    else if (new_order->price < base_order->left_order->price)
    {
        Order* old_left = base_order->left_order;
        base_order->left_order = new_order;
        new_order->prev_order = base_order;
        pullUpSellOrderFurther(new_order, old_left);
    }
    else if (new_order->price < base_order->right_order->price)
    {
        Order* old_right = base_order->right_order;
        base_order->right_order = new_order;
        new_order->prev_order = base_order;
        pullUpSellOrderFurther(new_order, old_right);
    }
    else 
    {
        // Right cause why not? and heavy emphasis elswhere to add to left
        pullUpSellOrderFurther(base_order->right_order, new_order);
    }
}

/*
Could change to iterative
*/
void pushDownSellOrder(ProductMarket* productMarket, Order* new_order)
{
    if (new_order->prev_order == NULL)
    {
        // DO NOTHING (AT THE TOP)
    }
    else if (new_order->price < new_order->prev_order->price)
    {
        if (new_order->prev_order->prev_order == NULL)
        {
            productMarket->lowest_sell_order = new_order;
        }
        Order* old_prev = new_order->prev_order;
        new_order->prev_order = new_order->prev_order->prev_order;
        if (old_prev->left_order == new_order)
        {
            old_prev->left_order = NULL;
        }
        else if (old_prev->right_order == new_order)
        {
            old_prev->right_order = NULL;
        }
        else 
        {
            // ERROR!!!!!!!
        }
        old_prev->prev_order = NULL;
        pullUpSellOrderFurther(new_order, old_prev);
        pushDownSellOrder(productMarket, new_order);
    }
}
