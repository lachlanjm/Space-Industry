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
	if (
		factoryIsInputStarved(&company->controlled_factory) == TRUE
		|| factoryIsAllOutputFull(&company->controlled_factory)
	) {
		const int employee_dec = MIN(
			company->controlled_factory.current_employee_num,
			(int)((float) company->controlled_factory.max_employee_num * CO_EMPLOYEE_DELTA_FACTOR)
		);

		if (decreaseEmployedLocalPopulation(
			getLocalPopulationByLocation(company->controlled_factory.location), employee_dec
		) == TRUE)
		{
			removeEmployees(&company->controlled_factory, employee_dec);
		}
	}
	else if (company->controlled_factory.current_employee_num >= company->controlled_factory.max_employee_num)
	{
		// Can't increase worker numbers
		// pass
	}
	else
	{
		const int employee_inc = MIN(
			company->controlled_factory.max_employee_num - company->controlled_factory.current_employee_num,
			(int)((float) company->controlled_factory.max_employee_num * CO_EMPLOYEE_DELTA_FACTOR)
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
	const double profit_factor_sell = (profit>=CO_MIN_PROFIT) ? 1 : (log10((double)((2*CO_MIN_PROFIT)-profit))-1);
	const double profit_factor_buy = (profit>=CO_MIN_PROFIT) ? 1 : (1/profit_factor_sell);

	for (int i = 0; i < company->controlled_factory.stockpiles_in_num; i++)
	{
		const QUANTITY_INT stockpile_ordered_quantity = 
			company->controlled_factory.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_in[i].product_type
		);
		const QUANTITY_INT stockpile_max = company->controlled_factory.stockpiles_in_max_quant[i];

		if (stockpile_ordered_quantity < stockpile_max - CO_ORDER_QUANTITY_MIN)
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
			company->controlled_factory.orders_in[i].offer_num = stockpile_max - stockpile_ordered_quantity;
		}

		if (company->controlled_factory.orders_in[i].offer_num > 0)
		{
			ProductMarket* productMarket = getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_in[i].product_type);

			const Product product_type = productMarket->product_type;
			const int base_price = ( 
				(getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) != 0) 
				? getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) 
				: ( (getMarketBuyAvgByProduct(product_type) != 0)
					? getMarketBuyAvgByProduct(product_type)
					: ( (getMarketSellAvgByProduct(product_type) != 0)
						? getMarketSellAvgByProduct(product_type)
						: ( (getMarketSellOfferAvgByProduct(product_type) != 0)
							? getMarketSellOfferAvgByProduct(product_type)
							: CO_DEFAULT_PRICE
			)))); // ?: needed to allow for const
			const double stockpile_factor = sqrt((double)company->controlled_factory.orders_in[i].offer_num) / CO_DESIRED_BUY_STOCKPILE_ROOT;

			// TODO TBU
			company->controlled_factory.orders_in[i].price = MAX(1, base_price * profit_factor_buy * stockpile_factor);

			if (company->controlled_factory.orders_in[i].price <= 0 || company->controlled_factory.orders_in[i].price > 1000000000) // FOR debugging
			{
				printf("b; %u, %f, %f, %u\n", base_price, profit_factor_buy, stockpile_factor, company->controlled_factory.orders_in[i].price);
			}

			if (resetBuyOrder(productMarket, &company->controlled_factory.orders_in[i])) 
			{
				printf("Failed to reset buy order\n");
			}
		}
	}

	for (int i = 0; i < company->controlled_factory.stockpiles_out_num; i++)
	{
		const QUANTITY_INT stockpile_free_quantity = 
			company->controlled_factory.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_out[i].product_type
		);
		if (company->controlled_factory.stockpiles_out[i].quantity 
		< *getOrderedOutQuantity(&company->controlled_factory, company->controlled_factory.stockpiles_out[i].product_type))
		{
			printf("stockpile_free_quantity = %u; %u, %u\n", stockpile_free_quantity, company->controlled_factory.stockpiles_out[i].quantity, *getOrderedOutQuantity(&company->controlled_factory, company->controlled_factory.stockpiles_out[i].product_type));
		}

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
							: CO_DEFAULT_PRICE
			)))); // ?: needed to allow for const
			const double stockpile_factor = CO_DESIRED_SELL_STOCKPILE_ROOT / sqrt((double)company->controlled_factory.orders_out[i].offer_num);

			company->controlled_factory.orders_out[i].price = MAX(1, base_price * profit_factor_sell * stockpile_factor);

			if (company->controlled_factory.orders_out[i].price <= 0 || company->controlled_factory.orders_out[i].price > 1000000000) // FOR debugging
			{
				printf("s; %u, %f, %f, %u\n", base_price, profit_factor_sell, stockpile_factor, company->controlled_factory.orders_out[i].price);
			}

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
		const QUANTITY_INT stockpile_ordered_quantity = 
			company->controlled_factory.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&company->controlled_factory, 
				company->controlled_factory.stockpiles_in[i].product_type
		);
		const QUANTITY_INT stockpile_max = company->controlled_factory.stockpiles_in_max_quant[i];

		if (stockpile_max - CO_ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			// Add to market
			 if (addBuyOrder(
				getProductMarketAtLocation(company->controlled_factory.location, company->controlled_factory.stockpiles_in[i].product_type),
				&company->controlled_factory.orders_in[i])
			) {
				printf("Failed to add buy order\n");
			}
			company->controlled_factory.orders_in[i].offer_num = stockpile_max - stockpile_ordered_quantity;
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
