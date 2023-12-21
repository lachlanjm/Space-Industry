#ifndef PRODUCT_MARKET_H
#define PRODUCT_MARKET_H

#include "Order.h"
#include "..\..\Production\Enums\Product.h"

typedef struct ProductMarket {
    Product product_type;
    Order* lowest_sell_order;
    Order* highest_buy_order;
} ProductMarket;

ProductMarket* newProductMarket(const Product product_type);
void assignNewProductMarket(ProductMarket* productMarket, const Product product_type);

void addSellOrder(ProductMarket* productMarket, Order* new_order);
Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);
void addBuyOrder(ProductMarket* productMarket, Order* new_order);
Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);

void removeBuyOrder(ProductMarket* buying_market, Order* buying_order);
void removeSellOrder(ProductMarket* selling_market, Order* selling_order);

void jump_attach_orders(Order* parent_order, Order* order, Order* child_order);
QUANTITY_INT match_orders(ProductMarket* selling_market, Order* selling_order, ProductMarket* buying_market, Order* buying_order);

void resetBuyOrder(ProductMarket* productMarket, Order* new_order);
void resetSellOrder(ProductMarket* productMarket, Order* new_order);

void pushDownBuyOrder(ProductMarket* productMarket, Order* new_order);
void pullUpBuyOrder(ProductMarket* productMarket, Order* new_order);

void push_down_buy_order_further(Order* base_order, Order* new_order);
void pull_up_sell_order_further(Order* base_order, Order* new_order);

void pullUpSellOrder(ProductMarket* productMarket, Order* new_order);
void pushDownSellOrder(ProductMarket* productMarket, Order* new_order);

#endif