#include "Company.h"

static COMPANY_ID_INT id_next = 0;

void assignNewCompanyValues(Company* const company)
{
	company->controlled_factories_num = 0;
	company->controlled_factories = NULL;
	company->wealth = 100000;
	company->id = id_next++;
} 

void addNewFactoryToCompany(Company* const company, const ProductionRecipe productionRecipe, const TransportNode location)
{
	if (company->controlled_factories_num == 0)
	{
		company->controlled_factories = calloc(++company->controlled_factories_num, sizeof(Factory*));
	}
	else
	{
		company->controlled_factories = realloc(
			company->controlled_factories, 
			++company->controlled_factories_num * sizeof(Factory*)
		);
	}
	company->controlled_factories[company->controlled_factories_num - 1] 
		= newFactoryCompany(company, productionRecipe, location);
}

Factory* loadAddNewFactoryToCompany(Company* const company)
{
	if (company->controlled_factories_num == 0)
	{
		company->controlled_factories = calloc(++company->controlled_factories_num, sizeof(Factory*));
	}
	else
	{
		company->controlled_factories = realloc(
			company->controlled_factories, 
			++company->controlled_factories_num * sizeof(Factory*)
		);
	}
	company->controlled_factories[company->controlled_factories_num - 1]
		= loadNewFactoryCompany();
	return company->controlled_factories[company->controlled_factories_num - 1];
}

void insertFundsCompany(Company* const company, const int funds)
{
	company->wealth += funds;
}

void withdrawFundsCompany(Company* const company, const int funds)
{
	if (company->wealth < funds) return; // reject payment
	company->wealth -= funds;
}

static inline IND_BOOL nearFullFactoryStockpileInputs(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		if (factory->stockpiles_in[i].quantity < CO_DESIRED_BUY_STOCKPILE_ROOT*CO_DESIRED_BUY_STOCKPILE_ROOT)
		{
			return FALSE;
		}
	}
	return TRUE;
}

static inline IND_BOOL nearEmptyFactoryStockpileOutputs(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		if (factory->stockpiles_out[i].quantity > CO_DESIRED_SELL_STOCKPILE_ROOT*CO_DESIRED_SELL_STOCKPILE_ROOT)
		{
			return FALSE;
		}
	}
	return TRUE;
}

static inline const int getBaseBuyPrice(const ProductMarket* const productMarket, const Government* const government, const Product product)
{
	return (getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) != 0) 
			? getAvgHistoryWtdAvgArray(&productMarket->buy_hist_array) 
			: ( (getGovMarketBuyAvgByProduct(government, product) != 0)
				? getGovMarketBuyAvgByProduct(government, product)
				: ( (getGovMarketSellAvgByProduct(government, product) != 0)
					? getGovMarketSellAvgByProduct(government, product)
					: ( (getMarketBuyAvgByProduct(product) != 0)
						? getMarketBuyAvgByProduct(product)
						: ( (getMarketSellAvgByProduct(product) != 0)
							? getMarketSellAvgByProduct(product)
							: ( (getMarketSellOfferAvgByProduct(product) != 0)
								? getMarketSellOfferAvgByProduct(product)
								: CO_DEFAULT_PRICE
		)))));
}
static inline const int getBaseSellPrice(const ProductMarket* const productMarket, const Government* const government, const Product product)
{
	return (getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) != 0) 
			? getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) 
			: ( (getGovMarketSellAvgByProduct(government, product) != 0)
				? getGovMarketSellAvgByProduct(government, product)
				: ( (getGovMarketBuyAvgByProduct(government, product) != 0)
					? getGovMarketBuyAvgByProduct(government, product)
					: ( (getMarketSellAvgByProduct(product) != 0)
						? getMarketSellAvgByProduct(product)
						: ( (getMarketBuyAvgByProduct(product) != 0)
							? getMarketBuyAvgByProduct(product)
							: ( (getMarketBuyOfferAvgByProduct(product) != 0)
								? getMarketBuyOfferAvgByProduct(product)
								: CO_DEFAULT_PRICE
		)))));
}

// TODO make it actually a market
static inline void updateEmployeeOffers(Company* const company)
{
	for (int i = 0; i < company->controlled_factories_num; i++)
	{
		Factory* const curr_fact = company->controlled_factories[i];
		const IND_BOOL input_full = nearFullFactoryStockpileInputs(curr_fact);
		const IND_BOOL output_empty = nearEmptyFactoryStockpileOutputs(curr_fact);
		const IND_BOOL hiring = (input_full && output_empty);
		if (!hiring) 
		{
			const int employee_dec = MIN(
				curr_fact->current_employee_num,
				(int)((float) curr_fact->max_employee_num * CO_EMPLOYEE_DELTA_FACTOR)
			);

			if (decreaseEmployedLocalPopulation(
				getLocalPopulationByLocation(curr_fact->location), employee_dec
			) == TRUE)
			{
				removeEmployees(curr_fact, employee_dec);
			}
		}
		else if (curr_fact->current_employee_num >= curr_fact->max_employee_num)
		{
			// Can't increase worker numbers
			// pass
		}
		else if (hiring)
		{
			const int employee_inc = MIN(
				curr_fact->max_employee_num - curr_fact->current_employee_num,
				(int)((float) curr_fact->max_employee_num * CO_EMPLOYEE_DELTA_FACTOR)
			);

			if (increaseEmployedLocalPopulation(
				getLocalPopulationByLocation(curr_fact->location), employee_inc
			) == TRUE)
			{
				addEmployees(curr_fact, employee_inc);
			}
		}
	}
}

static inline void updateOfferedPrices(Company* const company)
{
	for (int i = 0; i < company->controlled_factories_num; i++)
	{
		Factory* const curr_fact = company->controlled_factories[i];

		const long double profit = getAvgHistoryArrayAvg(&curr_fact->profit_history);
		const long double profit_factor_sell = (profit>=CO_MIN_PROFIT) ? 1 : (log10((double)((2*CO_MIN_PROFIT)-profit))-1);
		const long double profit_factor_buy = (profit>=CO_MIN_PROFIT) ? 1 : (1/profit_factor_sell);

		for (int i = 0; i < curr_fact->stockpiles_in_num; i++)
		{
			const QUANTITY_INT stockpile_ordered_quantity = 
				curr_fact->stockpiles_in[i].quantity
				+ *getOrderedInQuantity(
					curr_fact, 
					curr_fact->stockpiles_in[i].product_type
			);
			const QUANTITY_INT stockpile_max = curr_fact->stockpiles_in_max_quant[i];

			if (stockpile_ordered_quantity < stockpile_max - CO_ORDER_QUANTITY_MIN)
			{		
				if (curr_fact->orders_in[i].offer_num == 0)
				{
					// Add to market
					if (addBuyOrder(
						getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_in[i].product_type),
						&curr_fact->orders_in[i])
					) {
						printf("Failed to add buy order\n");
					}
				}
				curr_fact->orders_in[i].offer_num = stockpile_max - stockpile_ordered_quantity;
			}

			if (curr_fact->orders_in[i].offer_num > 0)
			{
				ProductMarket* productMarket = getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_in[i].product_type);

				const Product product_type = productMarket->product_type;
				// TODO TBU also divide by factory_num; also to better the calculation of the max allowable price
				const int base_price = MIN(
					company->wealth / MAX(1, curr_fact->stockpiles_in_num-1), 
					getBaseBuyPrice(productMarket, getGovernmentByLocation(productMarket->location), product_type)
				);
				const double stockpile_factor = sqrt((double)curr_fact->orders_in[i].offer_num) / CO_DESIRED_BUY_STOCKPILE_ROOT;

				// TODO TBU
				curr_fact->orders_in[i].price = MAX(1, base_price * profit_factor_buy * stockpile_factor);

				if (curr_fact->orders_in[i].price <= 0 || curr_fact->orders_in[i].price > 1000000000) // FOR debugging
				{
					printf("b; %u, %f, %f, %u\n", base_price, profit_factor_buy, stockpile_factor, curr_fact->orders_in[i].price);
				}

				if (resetBuyOrder(productMarket, &curr_fact->orders_in[i])) 
				{
					printf("Failed to reset buy order\n");
				}
			}
		}

		for (int i = 0; i < curr_fact->stockpiles_out_num; i++)
		{
			const QUANTITY_INT stockpile_free_quantity = 
				curr_fact->stockpiles_out[i].quantity
				- *getOrderedOutQuantity(
					curr_fact, 
					curr_fact->stockpiles_out[i].product_type
			);
			if (curr_fact->stockpiles_out[i].quantity 
			< *getOrderedOutQuantity(curr_fact, curr_fact->stockpiles_out[i].product_type))
			{
				printf("stockpile_free_quantity = %u; %u, %u\n", stockpile_free_quantity, curr_fact->stockpiles_out[i].quantity, *getOrderedOutQuantity(curr_fact, curr_fact->stockpiles_out[i].product_type));
			}

			if (stockpile_free_quantity > CO_ORDER_QUANTITY_MIN)
			{
				if (curr_fact->orders_out[i].offer_num == 0)
				{
					// Add to market
					if (addSellOrder(
						getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_out[i].product_type),
						&curr_fact->orders_out[i])
					) {
						printf("Failed to add sell order\n");
					}
				}
				curr_fact->orders_out[i].offer_num = stockpile_free_quantity;
			}

			if (curr_fact->orders_out[i].offer_num > 0)
			{
				// Re-calc selling price
				ProductMarket* productMarket = getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_out[i].product_type);
				
				const Product product_type = productMarket->product_type;
				const uint64_t base_price = getBaseSellPrice(productMarket, getGovernmentByLocation(productMarket->location), product_type);
				const double stockpile_factor = CO_DESIRED_SELL_STOCKPILE_ROOT / sqrt((double)curr_fact->orders_out[i].offer_num);

				curr_fact->orders_out[i].price = MAX(1, base_price * profit_factor_sell * stockpile_factor);

				if (curr_fact->orders_out[i].price <= 0 || curr_fact->orders_out[i].price > 1000000000) // FOR debugging
				{
					printf("s; %u, %f, %f, %u\n", base_price, profit_factor_sell, stockpile_factor, curr_fact->orders_out[i].price);
				}

				if (resetSellOrder(productMarket, &curr_fact->orders_out[i])) 
				{
					printf("Failed to reset sell order\n");
				}
			}
		}
	}
}

// TODO add employee wages into consideration
static inline void buildNewFactories(Company* const company)
{
	if (company->wealth > (CO_NEW_FACTORY_MATERIAL_COST + CO_NEW_FACTORY_LABOR_COST))
	{
		ProductionRecipe max_rcp = -1;
		TransportNode max_loc = -1;
		int max_profit = CO_NEW_FACTORY_MIN_RETURN;

		for (ProductionRecipe rcp = 0; rcp < PRODUCTION_RECIPE_COUNT; rcp++)
		{
			const int input_num = getNumOfInputs(rcp);
			const Stockpile* const inputs = getInputs(rcp);
			const int output_num = getNumOfOutputs(rcp);
			const Stockpile* const outputs = getOutputs(rcp);

			for (TransportNode loc = 0; loc < TRANSPORT_NODE_COUNT; loc++)
			{
				const Government* const gov = getGovernmentByLocation(loc);
				
				int costs = 0;
				int revenues = 0;
				for (int i = 0; i < input_num; i++)
					costs += inputs[i].quantity * getBaseBuyPrice(
						getProductMarketAtLocation(loc, inputs[i].product_type),
						gov,
						inputs[i].product_type
					);
				
				for (int i = 0; i < output_num; i++)
					revenues += outputs[i].quantity * getBaseSellPrice(
						getProductMarketAtLocation(loc, outputs[i].product_type),
						gov,
						outputs[i].product_type
					);

				if (revenues - costs > max_profit)
				{
					max_profit = revenues - costs;
					max_loc = loc;
					max_rcp = rcp;
				}
			}
		}

		if (max_loc != -1 && max_rcp != -1)
		{
			withdrawFundsCompany(company, CO_NEW_FACTORY_MATERIAL_COST + CO_NEW_FACTORY_LABOR_COST);
			
			// TODO ftm sends material costs to gov
			insertFundsGovernment(getGovernmentByLocation(max_loc), CO_NEW_FACTORY_MATERIAL_COST); 
			insertFundsLocalPopulation(getLocalPopulationByLocation(max_loc), CO_NEW_FACTORY_LABOR_COST);

			addNewFactoryToCompany(company, max_rcp, max_loc);
		}
	}
}

void loadCompanyAssignOrders(Company* const company)
{
	for (int i = 0; i < company->controlled_factories_num; i++)
	{
		Factory* const curr_fact = company->controlled_factories[i];
		for (int i = 0; i < curr_fact->stockpiles_in_num; i++)
		{
			const QUANTITY_INT stockpile_ordered_quantity = 
				curr_fact->stockpiles_in[i].quantity
				+ *getOrderedInQuantity(
					curr_fact, 
					curr_fact->stockpiles_in[i].product_type
			);
			const QUANTITY_INT stockpile_max = curr_fact->stockpiles_in_max_quant[i];

			if (stockpile_max - CO_ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
			{
				// Add to market
				if (addBuyOrder(
					getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_in[i].product_type),
					&curr_fact->orders_in[i])
				) {
					printf("Failed to add buy order\n");
				}
				curr_fact->orders_in[i].offer_num = stockpile_max - stockpile_ordered_quantity;
			}
			else 
			{
				curr_fact->orders_in[i].offer_num = 0;
			}
		}

		for (int i = 0; i < curr_fact->stockpiles_out_num; i++)
		{
			QUANTITY_INT stockpile_free_quantity = 
				curr_fact->stockpiles_out[i].quantity
				- *getOrderedOutQuantity(
					curr_fact, 
					curr_fact->stockpiles_out[i].product_type
			);
			if (CO_ORDER_QUANTITY_MIN < stockpile_free_quantity)
			{
				// Add to market
				if (addSellOrder(
					getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_out[i].product_type),
					&curr_fact->orders_out[i])
				) {
					printf("Failed to add sell order\n");
				}
				curr_fact->orders_out[i].offer_num = stockpile_free_quantity;
			}
			else 
			{
				curr_fact->orders_out[i].offer_num = 0;
			}
		}
	}
}

void assignLoadIdCompany(Company* const obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void processTickCompany(Company* const company)
{
	updateOfferedPrices(company);
	updateEmployeeOffers(company);
	
	for (int i = 0; i < company->controlled_factories_num; i++)
	{
		processTickFactory(company->controlled_factories[i]);
	}
}

void processBuildingTickCompany(Company* const company)
{
	buildNewFactories(company);
}


void cleanCompany(Company* company)
{
	for (int i = 0; i < company->controlled_factories_num; i++)
	{
		cleanFactory(company->controlled_factories[i]);
		free(company->controlled_factories[i]);
	}
	free(company->controlled_factories);
}
