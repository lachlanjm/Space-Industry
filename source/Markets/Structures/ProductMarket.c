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

void changeOfferedSellPrice(ProductMarket* productMarket, Order* order, const uint_fast16_t new_price)
{} // TODO Make pull funcs
void changeOfferedBuyPrice(ProductMarket* productMarket, Order* order, const uint_fast16_t new_price)
{} // TODO Make pull funcs

inline void addSellOrder(ProductMarket* productMarket, Order* new_order)
{
    pushUpOrder(productMarket->lowest_sell_order, new_order);
}

inline Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
    Order* order = newOrder(offering_factory, offer_num, price);
    addSellOrder(productMarket, order);
    return order;
}

inline void addBuyOrder(ProductMarket* productMarket, Order* new_order)
{
    pushDownOrder(productMarket->highest_buy_order, new_order);
}

inline Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
    Order* order = newOrder(offering_factory, offer_num, price);
    addBuyOrder(productMarket, order);
    return order;
}

void takeSellOrderOffMarket(ProductMarket* productMarket, Order* order); // Make pull funcs
void takeBuyOrderOffMarket(ProductMarket* productMarket, Order* order); // Make pull funcs

void matchOrders(ProductMarket* productMarket)
{
    while (productMarket->highest_buy_order->price >= productMarket->lowest_sell_order->price)
    {
        if (productMarket->highest_buy_order->offer_num > productMarket->lowest_sell_order->offer_num)
        {
            productMarket->highest_buy_order->offer_num -= productMarket->lowest_sell_order->offer_num;
            productMarket->lowest_sell_order->offer_num = 0;
            takeSellOrderOffMarket(productMarket, productMarket->lowest_sell_order);
        }
        else 
        {
            productMarket->lowest_sell_order->offer_num -= productMarket->highest_buy_order->offer_num;
            productMarket->highest_buy_order->offer_num = 0;
            takeBuyOrderOffMarket(productMarket, productMarket->highest_buy_order);

            if (productMarket->lowest_sell_order->offer_num == 0)
            {
                takeSellOrderOffMarket(productMarket, productMarket->highest_buy_order);
            }
        }
        
        // Mark for transport... (Add to transport market??? buyer pays for???)
    }
}
