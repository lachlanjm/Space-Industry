#ifndef PRODUCT_MARKET_H
#define PRODUCT_MARKET_H

#include "Order.h"
#include "..\..\Production\Enums\Product.h"

typedef struct ProductMarket {
    Product product_type;
    Order* lowest_sell_order;
    Order* highest_buy_order;
} ProductMarket;

inline ProductMarket* newProductMarket(const Product product_type);
inline void assignNewProductMarket(ProductMarket* productMarket, const Product product_type);

inline void addSellOrder(ProductMarket* productMarket, Order* new_order);
inline Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);
inline void addBuyOrder(ProductMarket* productMarket, Order* new_order);
inline Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price);

inline void resetBuyOrder(ProductMarket* productMarket, Order* new_order);
inline void resetSellOrder(ProductMarket* productMarket, Order* new_order);


#endif