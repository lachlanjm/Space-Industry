#ifndef MARKET_MAP_H
#define MARKET_MAP_H

#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Production\Enums\Product.h"
#include "..\Enums\TransportNode.h"
#include "..\..\..\History\HistoryWtdAvgArray.h"

#define MARKET_MAP_OFFER_STAT_REFRESH_TICK_RATE 32

void instantiateNewMarketMap(const int location_num, const int product_num);
ProductMarket* getProductMarketAtLocation(const TransportNode location, const Product product);

void recordMarketProductTransactionPrice(const Product product, const QUANTITY_INT quantity, const int buy_price, const int sell_price);
int getMarketBuyAvgByProduct(const Product product);
int getMarketSellAvgByProduct(const Product product);
int getMarketBuyOfferAvgByProduct(const Product product);
int getMarketSellOfferAvgByProduct(const Product product);

int getBuyOfferNumSumGlobal(const Product product);
int getSellOfferNumSumGlobal(const Product product);

HistoryWtdAvgArray* getMarketBuyHistoryWtdAvgArrByProduct(const Product product);
HistoryWtdAvgArray* getMarketSellHistoryWtdAvgArrByProduct(const Product product);

void processTickMarketMap(void);
void cleanMarketMap(void);

#endif
