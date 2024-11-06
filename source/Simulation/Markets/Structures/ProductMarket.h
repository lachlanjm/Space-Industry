#ifndef PRODUCT_MARKET_H
#define PRODUCT_MARKET_H

typedef struct ProductMarket ProductMarket;

#define PRODUCT_MARKET_ID_INT uint_least16_t

#include "Order.h"
#include "..\..\Production\Enums\Product.h"
#include "..\..\Environment\Enums\TransportNode.h"
#include "..\..\..\History\HistoryWtdAvgArray.h"

struct ProductMarket {
	TransportNode location;
	Product product_type;

	HistoryWtdAvgArray sell_hist_array;
	HistoryWtdAvgArray buy_hist_array;

	// Dynamically set
	int sell_order_num;
	int sell_order_arr_size;
	int buy_order_num;
	int buy_order_arr_size;
	Order** sell_order_arr;
	Order** buy_order_arr;

	PRODUCT_MARKET_ID_INT id;
};

ProductMarket* newProductMarket(const TransportNode location, const Product product_type);
void assignProductMarketValues(ProductMarket* productMarket, const TransportNode location, const Product product_type);

int addSellOrder(ProductMarket* productMarket, Order* new_order);
Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const ORDER_PRICE_INT price);
int addBuyOrder(ProductMarket* productMarket, Order* new_order);
Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const ORDER_PRICE_INT price);

int removeBuyOrder(ProductMarket* productMarket, Order* buying_order);
int removeBuyOrderIndexed(ProductMarket* productMarket, int index);
int removeSellOrder(ProductMarket* productMarket, Order* selling_order);
int removeSellOrderIndexed(ProductMarket* productMarket, int index);

QUANTITY_INT match_orders(ProductMarket* selling_market, Order* selling_order, ProductMarket* buying_market, Order* buying_order);
void swap_orders_arr(Order** order_1, Order** order_2);

int resetBuyOrder(ProductMarket* productMarket, Order* reset_order);
int resetBuyOrderIndexed(ProductMarket* productMarket, int index);
int resetSellOrder(ProductMarket* productMarket, Order* reset_order);
int resetSellOrderIndexed(ProductMarket* productMarket, int index);

void processTickProductMarket(ProductMarket* productMarket);
void cleanProductMarket(ProductMarket* productMarket);

#endif