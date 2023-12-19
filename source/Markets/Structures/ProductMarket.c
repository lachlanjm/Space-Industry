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

void removeBuyOrder(ProductMarket* buying_market, Order* buying_order)
{
    // Don't remove from factory, a quant of 0 === off the market
    if (buying_order->prev_order == NULL)
    {
        if (buying_order->left_order == NULL)
        {
            if (buying_order->right_order == NULL)
            {
                buying_market->highest_buy_order = NULL;
            }
            else
            {
                buying_market->highest_buy_order = buying_order->right_order;
                buying_order->right_order->prev_order = NULL;
            }
        }
        else if (buying_order->right_order == NULL)
        {
            buying_market->highest_buy_order = buying_order->left_order;
            buying_order->left_order->prev_order = NULL;
        }
        else if (buying_order->left_order->price >= buying_order->right_order->price)
        {
            buying_market->highest_buy_order = buying_order->left_order;
            buying_order->left_order->prev_order = NULL;
            push_down_buy_order_further(buying_order->left_order, buying_order->right_order);
        }
        else
        {
            buying_market->highest_buy_order = buying_order->right_order;
            buying_order->right_order->prev_order = NULL;
            push_down_buy_order_further(buying_order->right_order, buying_order->left_order);
        }
    }
    else
    {
        if (buying_order->left_order == NULL)
        {
            if (buying_order->right_order == NULL)
            {
                jump_attach_orders(buying_order->prev_order, buying_order, NULL);
            }
            else
            {
                jump_attach_orders(buying_order->prev_order, buying_order, buying_order->right_order);
            }
        }
        else if (buying_order->right_order == NULL)
        {
            jump_attach_orders(buying_order->prev_order, buying_order, buying_order->left_order);
        }
        else if (buying_order->left_order->price >= buying_order->right_order->price)
        {
            jump_attach_orders(buying_order->prev_order, buying_order, buying_order->left_order);
            push_down_buy_order_further(buying_order->left_order, buying_order->right_order);
        }
        else
        {
            jump_attach_orders(buying_order->prev_order, buying_order, buying_order->right_order);
            push_down_buy_order_further(buying_order->right_order, buying_order->left_order);
        }
    }
}

void removeSellOrder(ProductMarket* selling_market, Order* selling_order)
{
    // Don't remove from factory, a quant of 0 === off the market
    if (selling_order->prev_order == NULL)
    {
        if (selling_order->left_order == NULL)
        {
            if (selling_order->right_order == NULL)
            {
                selling_market->lowest_sell_order = NULL;
            }
            else
            {
                selling_market->lowest_sell_order = selling_order->right_order;
                selling_order->right_order->prev_order = NULL;
            }
        }
        else if (selling_order->right_order == NULL)
        {
            selling_market->lowest_sell_order = selling_order->left_order;
            selling_order->left_order->prev_order = NULL;
        }
        else if (selling_order->left_order->price <= selling_order->right_order->price)
        {
            selling_market->lowest_sell_order = selling_order->left_order;
            selling_order->left_order->prev_order = NULL;
            pull_up_sell_order_further(selling_order->left_order, selling_order->right_order);
        }
        else
        {
            selling_market->lowest_sell_order = selling_order->right_order;
            selling_order->right_order->prev_order = NULL;
            pull_up_sell_order_further(selling_order->right_order, selling_order->left_order);
        }
    }
    else
    {
        if (selling_order->left_order == NULL)
        {
            if (selling_order->right_order == NULL)
            {
                jump_attach_orders(selling_order->prev_order, selling_order, NULL);
            }
            else
            {
                jump_attach_orders(selling_order->prev_order, selling_order, selling_order->right_order);
            }
        }
        else if (selling_order->right_order == NULL)
        {
            jump_attach_orders(selling_order->prev_order, selling_order, selling_order->left_order);
        }
        else if (selling_order->left_order->price <= selling_order->right_order->price)
        {
            jump_attach_orders(selling_order->prev_order, selling_order, selling_order->left_order);
            pull_up_sell_order_further(selling_order->left_order, selling_order->right_order);
        }
        else
        {
            jump_attach_orders(selling_order->prev_order, selling_order, selling_order->right_order);
            pull_up_sell_order_further(selling_order->right_order, selling_order->left_order);
        }
    }
}

inline void jump_attach_orders(Order* parent_order, Order* order, Order* child_order)
{
    if (child_order != NULL)
    {
        child_order->prev_order = parent_order;
    }

    if (parent_order->left_order == order)
    {
        parent_order->left_order = child_order;
    }
    else if (parent_order->right_order == order)
    {
        parent_order->right_order = child_order;
    }
    else
    {
        /* error */
    }
}

QUANTITY_INT match_orders(ProductMarket* selling_market, Order* selling_order, ProductMarket* buying_market, Order* buying_order)
{
    QUANTITY_INT exchanged_num;
    if (selling_order->offer_num > buying_order->offer_num)
    {
        exchanged_num = buying_order->offer_num;
    }
    else
    {
        exchanged_num = selling_order->offer_num;
    }

    selling_order->offer_num -= exchanged_num;
    buying_order->offer_num -= exchanged_num;

    if (selling_order->offer_num == 0)
    {
        removeSellOrder(selling_market, selling_order);
    }

    if (buying_order->offer_num == 0)
    {
        removeBuyOrder(buying_market, buying_order);
    }

    return exchanged_num;
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
            push_down_buy_order_further(new_order, productMarket->highest_buy_order);
        }
        productMarket->highest_buy_order = new_order;
    }
    else
    {
        push_down_buy_order_further(productMarket->highest_buy_order, new_order);
    }
}

/*
Never replace base_order, only children
Could change to iterative
*/
void push_down_buy_order_further(Order* base_order, Order* new_order)
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
        push_down_buy_order_further(new_order, old_left);
    }
    else if (new_order->price > base_order->right_order->price)
    {
        Order* old_right = base_order->right_order;
        base_order->right_order = new_order;
        new_order->prev_order = base_order;
        push_down_buy_order_further(new_order, old_right);
    }
    else 
    {
        // Right cause why not? and heavy emphasis elswhere to add to left
        push_down_buy_order_further(base_order->right_order, new_order);
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
        push_down_buy_order_further(new_order, old_prev);
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
            pull_up_sell_order_further(new_order, productMarket->lowest_sell_order);
        }
        productMarket->lowest_sell_order = new_order;
    }
    else
    {
        pull_up_sell_order_further(productMarket->lowest_sell_order, new_order);
    }
}

/*
Never replace base_order, only children
Could change to iterative
*/
void pull_up_sell_order_further(Order* base_order, Order* new_order)
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
        pull_up_sell_order_further(new_order, old_left);
    }
    else if (new_order->price < base_order->right_order->price)
    {
        Order* old_right = base_order->right_order;
        base_order->right_order = new_order;
        new_order->prev_order = base_order;
        pull_up_sell_order_further(new_order, old_right);
    }
    else 
    {
        // Right cause why not? and heavy emphasis elswhere to add to left
        pull_up_sell_order_further(base_order->right_order, new_order);
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
        pull_up_sell_order_further(new_order, old_prev);
        pushDownSellOrder(productMarket, new_order);
    }
}
