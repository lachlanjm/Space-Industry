#include "Company.h"

static COMPANY_ID_INT id_next = 0;

void assignCompanyValues(Company* company, const ProductionRecipe productionRecipe, const TransportNode location)
{
	assignFactoryValuesCompany(&company->controlled_factory, company, productionRecipe, location);
	company->wealth = 100000;
	company->id = id_next++;
} 

void insertFundsCompany(Company* company, const int funds)
{
	company->wealth += funds;
}

void withdrawFundsCompany(Company* company, const int funds)
{
	if (company->wealth < funds) return; // reject payment
	company->wealth -= funds;
}

// TODO make it actually a market
void updateEmployeeOffers(Company* company)
{
	if (NULL) // TODO implement employee cutback
	{
		// Leftover production was too high
	}
	else if (company->controlled_factory.current_employee_num < company->controlled_factory.max_employee_num)
	{
		const int employee_inc = MIN(
			company->controlled_factory.max_employee_num - company->controlled_factory.current_employee_num,
			(int)((float) company->controlled_factory.max_employee_num * CO_EMPLOYEE_MAX_INC)
		);

		if (increaseEmployedLocalPopulation(
			getLocalPopulationByLocation(company->controlled_factory.location), employee_inc
		) == TRUE)
		{
			addEmployees(&company->controlled_factory, employee_inc);
		}
	}
}

void updateOfferedPrices(Company* company)
{
	const int profit = getAvgHistoryArrayAvg(&company->controlled_factory.profit_history);
	const double profit_factor_buy = MIN(1, pow((double)CO_MIN_PROFIT_FACTOR_BUY, (double)(profit-CO_MIN_PROFIT)));
	const double profit_factor_sell = MAX(1, pow((double)CO_MIN_PROFIT_FACTOR_SELL, (double)(CO_MIN_PROFIT-profit)));

	for (int i = 0; i < company->controlled_factory.stockpiles_in_num; i++)
	{
		QUANTITY_INT stockpile_ordered_quantity = 
			company->controlled_factory.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_in[i].product_type
		);

		if (stockpile_ordered_quantity < CO_STOCKPILE_FULL - CO_ORDER_QUANTITY_MIN)
		{		
			if (company->controlled_factory.orders_in[i].offer_num == 0)
			{
				// Add to market
				if (addBuyOrder(
					getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_in[i].product_type),
					&company->controlled_factory.orders_in[i])
				) {
					printf("Failed to add buy order\n");
				}
			}
			company->controlled_factory.orders_in[i].offer_num = CO_STOCKPILE_FULL - stockpile_ordered_quantity;
		}

		if (company->controlled_factory.orders_in[i].offer_num > 0)
		{
			ProductMarket* productMarket = getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_in[i].product_type);

			const int base_price = ( 
				(getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) != 0) 
				? getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) 
				: ( (getMarketBuyAvgByProduct(productMarket->product_type) != 0)
					? getMarketBuyAvgByProduct(productMarket->product_type)
					: ( (getMarketSellAvgByProduct(productMarket->product_type) != 0)
						? getMarketSellAvgByProduct(productMarket->product_type)
						: CO_DEFAULT_PRICE
			))); // ?: needed to allow for const

			// TODO TBU
			company->controlled_factory.orders_in[i].price = (
				base_price
				* profit_factor_buy
				* (sqrt((double)company->controlled_factory.orders_in[i].offer_num) / CO_DESIRED_BUY_STOCKPILE_ROOT)
			);

			if (resetBuyOrder(productMarket, &company->controlled_factory.orders_in[i])) 
			{
				printf("Failed to reset buy order\n");
			}
		}
	}

	for (int i = 0; i < company->controlled_factory.stockpiles_out_num; i++)
	{
		QUANTITY_INT stockpile_free_quantity = 
			company->controlled_factory.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_out[i].product_type
		);
		if (stockpile_free_quantity > CO_ORDER_QUANTITY_MIN)
		{
			if (company->controlled_factory.orders_out[i].offer_num == 0)
			{
				// Add to market
				if (addSellOrder(
					getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_out[i].product_type),
					&company->controlled_factory.orders_out[i])
				) {
					printf("Failed to add sell order\n");
				}
			}
			company->controlled_factory.orders_out[i].offer_num = stockpile_free_quantity;
		}

		if (company->controlled_factory.orders_out[i].offer_num > 0)
		{
			// Re-calc selling price
			ProductMarket* productMarket = getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_out[i].product_type);
			
			const int base_price = ( 
				(getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) != 0) 
				? getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) 
				: ( (getMarketSellAvgByProduct(productMarket->product_type) != 0)
					? getMarketSellAvgByProduct(productMarket->product_type)
					: ( (getMarketBuyAvgByProduct(productMarket->product_type) != 0)
						? getMarketBuyAvgByProduct(productMarket->product_type)
						: CO_DEFAULT_PRICE
			))); // ?: needed to allow for const

			company->controlled_factory.orders_out[i].price = (
				base_price
				* profit_factor_sell
				* (CO_DESIRED_SELL_STOCKPILE_ROOT / sqrt((double)company->controlled_factory.orders_out[i].offer_num))
			);

			if (resetSellOrder(productMarket, &company->controlled_factory.orders_out[i])) 
			{
				printf("Failed to reset sell order\n");
			}
		}
	}
}

void loadCompanyAssignOrders(Company* company)
{
	for (int i = 0; i < company->controlled_factory.stockpiles_in_num; i++)
	{
		QUANTITY_INT stockpile_ordered_quantity = 
			company->controlled_factory.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_in[i].product_type
		);

		if (CO_STOCKPILE_FULL - CO_ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			// Add to market
			 if (addBuyOrder(
				getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_in[i].product_type),
				&company->controlled_factory.orders_in[i])
			) {
				printf("Failed to add buy order\n");
			}
			company->controlled_factory.orders_in[i].offer_num = CO_STOCKPILE_FULL - stockpile_ordered_quantity;
		}
		else 
		{
			company->controlled_factory.orders_in[i].offer_num = 0;
		}
	}

	for (int i = 0; i < company->controlled_factory.stockpiles_out_num; i++)
	{
		QUANTITY_INT stockpile_free_quantity = 
			company->controlled_factory.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_out[i].product_type
		);
		if (CO_ORDER_QUANTITY_MIN < stockpile_free_quantity)
		{
			// Add to market
			if (addSellOrder(
				getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_out[i].product_type),
				&company->controlled_factory.orders_out[i])
			) {
				printf("Failed to add sell order\n");
			}
			company->controlled_factory.orders_out[i].offer_num = stockpile_free_quantity;
		}
		else 
		{
			company->controlled_factory.orders_out[i].offer_num = 0;
		}
	}
}

void assignLoadIdCompany(Company* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void processTickCompany(Company* company)
{
	updateOfferedPrices(company);
	updateEmployeeOffers(company);
	processTickFactory(&company->controlled_factory);
}

void cleanCompany(Company* company)
{
	cleanFactory(&company->controlled_factory);
}
