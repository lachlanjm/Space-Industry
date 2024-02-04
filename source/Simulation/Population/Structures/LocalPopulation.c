#include "LocalPopulation.h"

static LOCAL_POPULATION_ID_INT id_next = 0;

LocalPopulation* newLocalPopulation(const TransportNode location, const uint32_t population_number)
{
	LocalPopulation* population = calloc(1, sizeof(LocalPopulation));
	assignLocalPopulationValues(population, location, population_number);
	return population;
}

void assignLocalPopulationValues(LocalPopulation* population, const TransportNode location, const uint32_t population_number)
{
	population->population_number = population_number;
	assignFactoryValues(&population->population_centre, Population_Consumption, location);

	population->id = id_next++;
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
			if (LP_DESIRED_STOCKPILE_MAX < stockpile_ordered_quantity)
			{
				// Lower offered price
				population->population_centre.orders_in[i].price *= LP_DECREASE_PRICE_FACTOR;
				if (resetBuyOrder(
					getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_in[i].product_type),
					&population->population_centre.orders_in[i])
				) {
					printf("Failed to reset buy order\n");
				}
			}
			else if (LP_DESIRED_STOCKPILE_MIN > stockpile_ordered_quantity)
			{
				// Raise offered price
				population->population_centre.orders_in[i].price *= LP_INCREASE_PRICE_FACTOR;
				if (resetBuyOrder(
					getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_in[i].product_type),
					&population->population_centre.orders_in[i])
				) {
					printf("Failed to reset buy order\n");
				}
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
		if (LP_ORDER_QUANTITY_MIN < stockpile_free_quantity)
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
			if (LP_DESIRED_STOCKPILE_MAX < stockpile_free_quantity)
			{
				// Lower selling price
				population->population_centre.orders_out[i].price *= LP_DECREASE_PRICE_FACTOR;
				if (resetSellOrder(
					getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_out[i].product_type),
					&population->population_centre.orders_out[i])
				) {
					printf("Failed to reset sell order\n");
				}
			}
			else if (LP_DESIRED_STOCKPILE_MIN > stockpile_free_quantity)
			{
				// Raise selling price
				population->population_centre.orders_out[i].price *= LP_INCREASE_PRICE_FACTOR;
				if (resetSellOrder(
					getProductMarketAtLocation(population->population_centre.location, population->population_centre.stockpiles_out[i].product_type),
					&population->population_centre.orders_out[i])
				) {
					printf("Failed to reset sell order\n");
				}
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

// TODO TBU: CUSTOM MANAGEMENT OF FACTORY
void processTickLocalPopulation(LocalPopulation* population)
{
	population->population_centre.processing_speed = population->population_number / CONSUMPTION_RATE_DIVISOR;
	processTickFactory(&population->population_centre);
	updateLocalPopulationOfferedPrices(population);
}

void cleanLocalPopulation(LocalPopulation* population)
{
	cleanFactory(&population->population_centre);
}
