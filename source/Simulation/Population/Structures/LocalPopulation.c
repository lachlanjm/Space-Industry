#include "LocalPopulation.h"

static int local_population_count = 0;
static LocalPopulation* __static_local_populations = NULL;
void setTransportNodeCountLocalPopulationStatic(const int transport_node_count)
{
	__static_local_populations = (LocalPopulation*) calloc(transport_node_count, sizeof(LocalPopulation));
	local_population_count = transport_node_count;
}

int getLocalPopulationNum(void)
{
	return local_population_count;
}

LocalPopulation* getLocalPopulationByLocation(const TransportNode location)
{
	if (location >= local_population_count) { return NULL; }
	return &__static_local_populations[location];
}

void cleanTransportNodeCountLocalPopulationStatic(void)
{
	free(__static_local_populations);
	local_population_count = 0;
}

static LOCAL_POPULATION_ID_INT id_next = 0;

void assignLocalPopulationValues(const TransportNode location, const uint32_t population_number)
{
	LocalPopulation* population = getLocalPopulationByLocation(location);

	population->population_number = population_number;
	population->employed_number = 0;
	assignFactoryValuesLocalPopulation(&population->population_centre, location);
	population->population_centre.current_employee_num = population->population_centre.max_employee_num;

	population->wealth = 100000;

	population->id = id_next++;
}

// Will not clean or destroy `origin`; also does only a shallow copy
void moveLocalPopulationToStaticArray(LocalPopulation* origin, const TransportNode location)
{
	LocalPopulation* dest = getLocalPopulationByLocation(location);
	cleanLocalPopulation(dest);

	memcpy(dest, origin, sizeof(LocalPopulation));
	dest->population_centre.management = dest;

	for (int i = 0; i < dest->population_centre.stockpiles_in_num; i++)
	{
		dest->population_centre.orders_in[i].offering_factory = dest;
	}
	for (int i = 0; i < dest->population_centre.stockpiles_out_num; i++)
	{
		dest->population_centre.orders_out[i].offering_factory = dest;
	}
	
	reassignOrderOfferingPtrs(&dest->population_centre);
}

void assignLoadIdLocalPopulation(LocalPopulation* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void updateLocalPopulationOfferedPrices(LocalPopulation* population)
{
	const int profit = getAvgHistoryArrayAvg(&population->population_centre.profit_history);
	const double profit_factor_sell = (profit>=LP_MIN_PROFIT) ? 1 : (log10((double)((2*LP_MIN_PROFIT)-profit))-1);
	const double profit_factor_buy = (profit>=LP_MIN_PROFIT) ? 1 : (1/profit_factor_sell);

	for (int i = 0; i < population->population_centre.stockpiles_in_num; i++)
	{
		QUANTITY_INT stockpile_ordered_quantity = 
			population->population_centre.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&population->population_centre, 
				population->population_centre.stockpiles_in[i].product_type
		);

		if (stockpile_ordered_quantity < LP_STOCKPILE_FULL - LP_ORDER_QUANTITY_MIN)
		{		
			if (population->population_centre.orders_in[i].offer_num == 0)
			{
				// Add to market
				if (addBuyOrder(
					getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_in[i].product_type),
					&population->population_centre.orders_in[i])
				) {
					printf("Failed to add buy order\n");
				}
			}
			population->population_centre.orders_in[i].offer_num = LP_STOCKPILE_FULL - stockpile_ordered_quantity;
		}

		if (population->population_centre.orders_in[i].offer_num > 0)
		{
			ProductMarket* productMarket = getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_in[i].product_type);

			const Product product_type = productMarket->product_type;
			// TODO TBU better the calculation of the max allowable price
			const int base_price = MIN(
				population->wealth / MAX(1, population->population_centre.stockpiles_in_num-1), ( 
					(getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) != 0) 
					? getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) 
					: ( (getMarketBuyAvgByProduct(product_type) != 0)
						? getMarketBuyAvgByProduct(product_type)
						: ( (getMarketSellAvgByProduct(product_type) != 0)
							? getMarketSellAvgByProduct(product_type)
							: ( (getMarketSellOfferAvgByProduct(product_type) != 0)
								? getMarketSellOfferAvgByProduct(product_type)
								: LP_DEFAULT_PRICE
			))))); // ?: needed to allow for const
			const double stockpile_factor = sqrt((double)population->population_centre.orders_in[i].offer_num) / LP_DESIRED_BUY_STOCKPILE_ROOT;

			// TODO TBU
			population->population_centre.orders_in[i].price = MAX(1, base_price * profit_factor_buy * stockpile_factor);

			if (resetBuyOrder(productMarket, &population->population_centre.orders_in[i])) 
			{
				printf("");
				printf("Failed to reset buy order; PM=%x, Order=%x\n", productMarket, &population->population_centre.orders_in[i]);
			}
		}
	}

	for (int i = 0; i < population->population_centre.stockpiles_out_num; i++)
	{
		QUANTITY_INT stockpile_free_quantity = 
			population->population_centre.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&population->population_centre, 
				population->population_centre.stockpiles_out[i].product_type
		);
		if (stockpile_free_quantity > LP_ORDER_QUANTITY_MIN)
		{
			if (population->population_centre.orders_out[i].offer_num == 0)
			{
				// Add to market
				if (addSellOrder(
					getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_out[i].product_type),
					&population->population_centre.orders_out[i])
				) {
					printf("Failed to add sell order\n");
				}
			}
			population->population_centre.orders_out[i].offer_num = stockpile_free_quantity;
		}

		if (population->population_centre.orders_out[i].offer_num > 0)
		{
			// Re-calc selling price
			ProductMarket* productMarket = getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_out[i].product_type);
			
			const Product product_type = productMarket->product_type;
			const uint64_t base_price = ( 
				(getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) != 0) 
				? getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) 
				: ( (getMarketSellAvgByProduct(product_type) != 0)
					? getMarketSellAvgByProduct(product_type)
					: ( (getMarketBuyAvgByProduct(product_type) != 0)
						? getMarketBuyAvgByProduct(product_type)
						: ( (getMarketBuyOfferAvgByProduct(product_type) != 0)
							? getMarketBuyOfferAvgByProduct(product_type)
							: LP_DEFAULT_PRICE
			)))); // ?: needed to allow for const
			const double stockpile_factor = LP_DESIRED_SELL_STOCKPILE_ROOT / sqrt((double)population->population_centre.orders_out[i].offer_num);

			// TODO TBU
			population->population_centre.orders_out[i].price = MAX(1, base_price * profit_factor_sell * stockpile_factor);

			if (resetSellOrder(productMarket, &population->population_centre.orders_out[i])) 
			{
				printf("Failed to reset sell order\n");
			}
		}
	}
}

void loadLocalPopulationAssignOrders(LocalPopulation* population)
{
	for (int i = 0; i < population->population_centre.stockpiles_in_num; i++)
	{
		QUANTITY_INT stockpile_ordered_quantity = 
			population->population_centre.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&population->population_centre, 
				population->population_centre.stockpiles_in[i].product_type
		);

		if (LP_STOCKPILE_FULL - LP_ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			// Add to market
			 if (addBuyOrder(
				getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_in[i].product_type),
				&population->population_centre.orders_in[i])
			) {
				printf("Failed to add buy order\n");
			}
			population->population_centre.orders_in[i].offer_num = LP_STOCKPILE_FULL - stockpile_ordered_quantity;
		}
		else 
		{
			population->population_centre.orders_in[i].offer_num = 0;
		}
	}

	for (int i = 0; i < population->population_centre.stockpiles_out_num; i++)
	{
		QUANTITY_INT stockpile_free_quantity = 
			population->population_centre.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&population->population_centre, 
				population->population_centre.stockpiles_out[i].product_type
		);
		
		if (LP_ORDER_QUANTITY_MIN < stockpile_free_quantity)
		{
			// Add to market
			if (addSellOrder(
				getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_out[i].product_type),
				&population->population_centre.orders_out[i])
			) {
				printf("Failed to add sell order\n");
			}
			population->population_centre.orders_out[i].offer_num = stockpile_free_quantity;
		}
		else 
		{
			population->population_centre.orders_out[i].offer_num = 0;
		}
	}
}

void insertFundsLocalPopulation(LocalPopulation* population, const int funds)
{
	population->wealth += funds;

	recordInsertFundsFactory(&population->population_centre, funds);
}

void withdrawFundsLocalPopulation(LocalPopulation* population, const int funds)
{
	if (population->wealth < funds) return; // reject payment
	population->wealth -= funds;

	recordWithdrawFundsFactory(&population->population_centre, funds);
}

IND_BOOL increaseEmployedLocalPopulation(LocalPopulation* population, const int jobs)
{
	if (population->employed_number + jobs > population->population_number) return FALSE;
	population->employed_number += jobs;
	return TRUE;
}

IND_BOOL decreaseEmployedLocalPopulation(LocalPopulation* population, const int jobs)
{
	// if (population->employed_number - jobs < 0) { return FALSE; } // TODO SHOULD NEVER HAPPEN
	population->employed_number -= jobs;
	return TRUE;
}

void processTickLocalPopulation(LocalPopulation* population)
{
	population->population_centre.processing_speed = population->population_number / CONSUMPTION_RATE_DIVISOR;
	processTickFactoryLocalPopulation(&population->population_centre);
	updateLocalPopulationOfferedPrices(population);
}

void cleanLocalPopulation(LocalPopulation* population)
{
	cleanFactory(&population->population_centre);
}
