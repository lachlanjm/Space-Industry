#ifndef MARKET_MAP_H
#define MARKET_MAP_H

#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Production\Enums\Product.h"
#include "..\Enums\TransportNode.h"

void instantiateNewMarketMap(const int location_num, const int product_num);
ProductMarket* getProductMarketAtLocation(const TransportNode location, const Product product);
void processTickMarketMap(void);
void cleanMarketMap(void);

#endif
