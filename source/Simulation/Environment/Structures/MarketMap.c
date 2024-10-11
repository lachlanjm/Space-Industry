#include "MarketMap.h"

static ProductMarket** __product_market_at_location_arr__ = NULL;
static int __location_num = 0;
static int __product_num = 0;

void instantiateNewMarketMap(const int location_num, const int product_num)
{
	__product_market_at_location_arr__ = calloc(location_num, sizeof(ProductMarket*));
	if (__product_market_at_location_arr__ == NULL) return;

	for (int x=0; x<location_num; x++)
	{
		__product_market_at_location_arr__[x] = calloc(product_num, sizeof(ProductMarket));
		if (__product_market_at_location_arr__[x] == NULL) return;  // TODO handle error memory leak

		for (int y=0; y<product_num; y++)
		{
			assignProductMarketValues(&__product_market_at_location_arr__[x][y], x, y);
		}
	}

	__location_num = location_num;
	__product_num = product_num;
}

ProductMarket* getProductMarketAtLocation(const TransportNode location, const Product product) 
{
	if (__product_market_at_location_arr__ == NULL) return NULL;
	if (location >= __location_num) return NULL;
	if (product >= __product_num) return NULL;
	return &__product_market_at_location_arr__[location][product];
}

void processTickMarketMap(void)
{
	for (int x=0; x<__location_num; x++)
	{
		for (int y=0; y<__product_num; y++)
		{
			processTickProductMarket(&__product_market_at_location_arr__[x][y]);
		}
	}
}

void cleanMarketMap(void)
{
	for (int x=0; x<__location_num; x++)
	{
		for (int y=0; y<__product_num; y++)
		{
			cleanProductMarket(&__product_market_at_location_arr__[x][y]);
		}
		free(__product_market_at_location_arr__[x]);
	}
	free(__product_market_at_location_arr__);
	__product_market_at_location_arr__ = NULL;
	__location_num = 0;
	__product_num = 0;
}
