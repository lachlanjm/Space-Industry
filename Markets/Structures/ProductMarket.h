#ifndef PRODUCT_MARKET_H
#define PRODUCT_MARKET_H

#include "Order.h"
#include "..\..\Production\Enums\Product.h"

typedef struct ProductMarket {
    Product product_type;
    Order* lowest_sell_order;
    Order* highest_buy_order;
} ProductMarket;

ProductMarket* newProductMarket (Product product_type);

inline void addSellOrder(ProductMarket* productMarket, Order* new_order);
inline Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);
inline void addBuyOrder(ProductMarket* productMarket, Order* new_order);
inline Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);

void changeOfferedSellPrice(ProductMarket* productMarket, Order* order, const uint_fast16_t new_price);
void changeOfferedBuyPrice(ProductMarket* productMarket, Order* order, const uint_fast16_t new_price);

void takeSellOrderOffMarket(ProductMarket* productMarket, Order* order);
void takeBuyOrderOffMarket(ProductMarket* productMarket, Order* order);

void matchOrders(ProductMarket* productMarket);

#endif