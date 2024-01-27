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

void removeBuyOrder(ProductMarket* productMarket, Order* buying_order);
void removeSellOrder(ProductMarket* productMarket, Order* selling_order);

QUANTITY_INT match_orders(ProductMarket* selling_market, Order* selling_order, ProductMarket* buying_market, Order* buying_order);
void swap_orders(Order* parent_order, Order* child_order);

void resetBuyOrder(ProductMarket* productMarket, Order* reset_order);
void resetSellOrder(ProductMarket* productMarket, Order* reset_order);

#endif