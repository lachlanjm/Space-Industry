#ifndef MARKET_MAP_H
#define MARKET_MAP_H

#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Production\Enums\Product.h"
#include "..\Enums\TransportNode.h"

inline ProductMarket getProductMarketAtLocation(const TransportNode location, const Product product);

#endif
