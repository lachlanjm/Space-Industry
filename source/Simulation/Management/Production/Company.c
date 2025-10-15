#include "Company.h"

static COMPANY_ID_INT id_next = 0;

static int factories_deletion_purgatory_num = 0;
static Factory** factories_deletion_purgatory = NULL;

void assignNewCompanyValues(Company* const company)
{
	company->controlled_factories_num = 0;
	company->deficit_ticks = NULL;
	company->controlled_factories = NULL;
	company->wealth = 100000;
	company->id = id_next++;
} 

void addNewFactoryToCompany(Company* const company, const ProductionRecipe productionRecipe, const TransportNode location)
{
	if (company->controlled_factories_num == 0)
	{
		company->deficit_ticks = calloc(++company->controlled_factories_num, sizeof(int));
		company->controlled_factories = calloc(company->controlled_factories_num, sizeof(Factory*));
	}
	else
	{
		company->deficit_ticks = realloc(
			company->deficit_ticks, 
			++company->controlled_factories_num * sizeof(int)
		);
		company->controlled_factories = realloc(
			company->controlled_factories, 
			company->controlled_factories_num * sizeof(Factory*)
		);
	}
	company->deficit_ticks[company->controlled_factories_num - 1] = 0;
	company->controlled_factories[company->controlled_factories_num - 1] 
		= newFactoryCompany(company, productionRecipe, location);
}

static inline void addFactoryToPurgatory(const Factory* const factory)
{
	if (factories_deletion_purgatory_num++ == 0)
	{
		factories_deletion_purgatory = malloc(factories_deletion_purgatory_num * sizeof(Factory*));
	}
	else 
	{
		factories_deletion_purgatory = realloc(factories_deletion_purgatory, factories_deletion_purgatory_num * sizeof(Factory*));
	}
	factories_deletion_purgatory[factories_deletion_purgatory_num-1] = factory;
}

static inline void deleteFactoryFromPurgatory(Factory* const factory, const int index)
{
	if (--factories_deletion_purgatory_num == 0)
	{
		free(factories_deletion_purgatory);
		factories_deletion_purgatory = NULL;
	}
	else 
	{
		factories_deletion_purgatory[index] = factories_deletion_purgatory[factories_deletion_purgatory_num];
		factories_deletion_purgatory = realloc(factories_deletion_purgatory, factories_deletion_purgatory_num * sizeof(Factory*));
	}

	cleanFactory(factory);
	free(factory);
}

static inline IND_BOOL checkNoOrderedInOrOut(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_in_num; i++) if (factory->ordered_in[i] > 0) return FALSE;
	for (int i = 0; i < factory->stockpiles_out_num; i++) if (factory->ordered_out[i] > 0) return FALSE;
	return TRUE;
}

void cleanUpFactoryPurgatoryStatic(void)
{
	for (int i = 0; i < factories_deletion_purgatory_num; i++)
	{
		Factory* const factory = factories_deletion_purgatory[i];

		if (checkNoOrderedInOrOut(factory) == TRUE) deleteFactoryFromPurgatory(factory, i);
	}
}

static inline void destroyFactoryFromCompany(Company* const company, const int index)
{
	Factory* const old_factory = company->controlled_factories[index];

	company->deficit_ticks[index] = company->deficit_ticks[--company->controlled_factories_num];
	company->controlled_factories[index] = company->controlled_factories[company->controlled_factories_num];

	if (company->controlled_factories_num > 0)
	{
		company->deficit_ticks = realloc(
			company->deficit_ticks, 
			company->controlled_factories_num * sizeof(int)
		);
		company->controlled_factories = realloc(
			company->controlled_factories, 
			company->controlled_factories_num * sizeof(Factory*)
		);
	}
	else
	{
		free(company->deficit_ticks);
		free(company->controlled_factories);
		company->controlled_factories_num = 0;
	}

	removeOrders(old_factory);
	addFactoryToPurgatory(old_factory);
}

Factory* loadAddNewFactoryToCompany(Company* const company)
{
	if (company->controlled_factories_num == 0)
	{
		company->deficit_ticks = calloc(++company->controlled_factories_num, sizeof(int));
		company->controlled_factories = calloc(company->controlled_factories_num, sizeof(Factory*));
	}
	else
	{
		company->deficit_ticks = realloc(
			company->deficit_ticks, 
			++company->controlled_factories_num * sizeof(int)
		);
		company->controlled_factories = realloc(
			company->controlled_factories, 
			company->controlled_factories_num * sizeof(Factory*)
		);
	}
	company->deficit_ticks[company->controlled_factories_num - 1] = 0;
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

static inline IND_BOOL oneNearEmptyFactoryStockpileInputs(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		if (factory->stockpiles_in[i].quantity <= CO_DESIRED_BUY_STOCKPILE_MIN)
		{
			return TRUE;
		}
	}
	return FALSE;
}

static inline IND_BOOL allNearFullFactoryStockpileInputs(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		if (factory->stockpiles_in[i].quantity < CO_DESIRED_BUY_STOCKPILE_MAX)
		{
			return FALSE;
		}
	}
	return TRUE;
}

static inline IND_BOOL oneNearFullFactoryStockpileOutputs(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		if (factory->stockpiles_out[i].quantity >= CO_DESIRED_SELL_STOCKPILE_MAX)
		{
			return TRUE;
		}
	}
	return FALSE;
}

static inline IND_BOOL allNearEmptyFactoryStockpileOutputs(const Factory* const factory)
{
	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		if (factory->stockpiles_out[i].quantity > CO_DESIRED_SELL_STOCKPILE_MIN)
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
			: ( (getGovMarketSellAvgByProduct(government, product) != 0)
				? getGovMarketSellAvgByProduct(government, product)
				: ( (getGovMarketBuyAvgByProduct(government, product) != 0)
					? getGovMarketBuyAvgByProduct(government, product)
					: ( (getMarketSellAvgByProduct(product) != 0)
						? getMarketSellAvgByProduct(product)
						: ( (getMarketBuyAvgByProduct(product) != 0)
							? getMarketBuyAvgByProduct(product)
							: ( (getMarketSellOfferAvgByProduct(product) != 0)
								? getMarketSellOfferAvgByProduct(product)
								: CO_DEFAULT_PRICE
		)))));
}
static inline const int getBaseSellPrice(const ProductMarket* const productMarket, const Government* const government, const Product product)
{
	return (getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) != 0) 
			? getAvgHistoryWtdAvgArray(&productMarket->sell_hist_array) 
			: ( (getGovMarketBuyAvgByProduct(government, product) != 0)
				? getGovMarketBuyAvgByProduct(government, product)
				: ( (getGovMarketSellAvgByProduct(government, product) != 0)
					? getGovMarketSellAvgByProduct(government, product)
					: ( (getMarketBuyAvgByProduct(product) != 0)
						? getMarketBuyAvgByProduct(product)
						: ( (getMarketSellAvgByProduct(product) != 0)
							? getMarketSellAvgByProduct(product)
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

		const IND_BOOL input_empty = oneNearEmptyFactoryStockpileInputs(curr_fact);
		const IND_BOOL input_full = allNearFullFactoryStockpileInputs(curr_fact);
		const IND_BOOL output_empty = allNearEmptyFactoryStockpileOutputs(curr_fact);
		const IND_BOOL output_full = oneNearFullFactoryStockpileOutputs(curr_fact);

		IND_BOOL hiring = FALSE;
		IND_BOOL firing = FALSE;
		
		if (curr_fact->profit_history.avg < 0)
		{
			firing = TRUE;
		}
		else if (input_empty || output_full)
		{
			firing = TRUE;
		}
		else if (input_full || output_empty) // effectively [in this elseif order] (input_full && !output_full) || (output_empty && !input_empty)
		{
			hiring = TRUE;
		}

		if (firing && curr_fact->current_employee_num > 0) 
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
		else if (hiring && curr_fact->current_employee_num <= curr_fact->max_employee_num)
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

		int cost_of_inputs = 0;

		for (int i = 0; i < curr_fact->stockpiles_in_num; i++)
		{
			const QUANTITY_INT stockpile_ordered_quantity = 
				curr_fact->stockpiles_in[i].quantity
				+ *getOrderedInQuantity(
					curr_fact, 
					curr_fact->stockpiles_in[i].product_type
			);
			const QUANTITY_INT stockpile_max = curr_fact->stockpiles_in_max_quant[i];

			curr_fact->orders_in[i].offer_num = stockpile_max - stockpile_ordered_quantity;

			if (curr_fact->orders_in[i].offer_num > 0)
			{
				ProductMarket* productMarket = getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_in[i].product_type);

				const Product product_type = productMarket->product_type;
				// TODO TBU also divide by factory_num; also to better the calculation of the max allowable price
				const int base_price = MIN(
					company->wealth / MAX(1, curr_fact->stockpiles_in_num-1), 
					getBaseBuyPrice(productMarket, getGovernmentByLocation(productMarket->location), product_type)
				);
				const double stockpile_factor = sqrt((double)curr_fact->orders_in[i].offer_num) / CO_ORDER_DESIRED_BUY_STOCKPILE_ROOT;

				// TODO TBU
				const uint_fast64_t market_based_price = (uint_fast64_t) MAX(1, base_price * profit_factor_buy * stockpile_factor);
				const uint_fast64_t wealth_based_price = (uint_fast64_t) MAX(1, 
					2 * (double)company->wealth 
					/ (double)(curr_fact->orders_in[i].offer_num 
						* company->controlled_factories_num 
						* curr_fact->stockpiles_in_num
					));
				curr_fact->orders_in[i].price = MIN(market_based_price, wealth_based_price);

				// FOR debugging
				if (curr_fact->orders_in[i].price <= 0 || curr_fact->orders_in[i].price > 1000000000) printf("b; %u, %f, %f, %u\n", base_price, profit_factor_buy, stockpile_factor, curr_fact->orders_in[i].price);

				if (resetBuyOrder(productMarket, &curr_fact->orders_in[i])) 
				{
					printf("Failed to reset buy order\n");
				}
			}

			cost_of_inputs += curr_fact->orders_in[i].price * getInputs(curr_fact->productionRecipe)[i].quantity;
		}

		const int total_cost_of_inputs = cost_of_inputs;
		const long double min_output_price_per_prod = total_cost_of_inputs / getNumOfOutputs(curr_fact->productionRecipe);

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

			curr_fact->orders_out[i].offer_num = stockpile_free_quantity;

			if (curr_fact->orders_out[i].offer_num > 0)
			{
				// Re-calc selling price
				ProductMarket* productMarket = getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_out[i].product_type);
				
				const Product product_type = productMarket->product_type;
				const uint64_t base_price = getBaseSellPrice(productMarket, getGovernmentByLocation(productMarket->location), product_type);
				const double stockpile_factor = CO_ORDER_DESIRED_SELL_STOCKPILE_ROOT / sqrt((double)curr_fact->orders_out[i].offer_num);

				const long double min_output_price = min_output_price_per_prod / getOutputs(curr_fact->productionRecipe)[i].quantity;
			
				curr_fact->orders_out[i].price = MAX(MAX(1, min_output_price), base_price * profit_factor_sell * stockpile_factor);

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
				
				int throughput = CO_MAX_THROUGHPUT_NUM;
				for (int i = 0; i < input_num; i++)
					throughput = MIN(throughput, (int) (
						(getSellOfferNumSumGlobal(inputs[i].product_type) - getBuyOfferNumSumGlobal(inputs[i].product_type)) 
						/ (int)(inputs[i].quantity * CO_BUY_THROUGHPUT_FACTOR))
					);
				for (int i = 0; i < output_num; i++)
					throughput = MIN(throughput, (int) (
						(getBuyOfferNumSumGlobal(outputs[i].product_type) - getSellOfferNumSumGlobal(outputs[i].product_type)) 
						/ (int)(outputs[i].quantity * CO_SELL_THROUGHPUT_FACTOR))
					);

				const int profit = (revenues - costs) * MAX(0, throughput);
				if (profit > max_profit && throughput > 0)
				{
					max_profit = profit;
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
			curr_fact->orders_in[i].offer_num = stockpile_max - stockpile_ordered_quantity;

			// Add to market
			if (addBuyOrder(
				getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_in[i].product_type),
				&curr_fact->orders_in[i])
			) {
				printf("Failed to add buy order\n");
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
			curr_fact->orders_out[i].offer_num = stockpile_free_quantity;

			// Add to market
			if (addSellOrder(
				getProductMarketAtLocation(curr_fact->location, curr_fact->stockpiles_out[i].product_type),
				&curr_fact->orders_out[i])
			) {
				printf("Failed to add sell order\n");
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
		if (getAvgHistoryArrayAvg(&company->controlled_factories[i]->profit_history) < 0) company->deficit_ticks[i]++;
		else company->deficit_ticks[i] = MAX(--company->deficit_ticks[i], 0);

		if (company->deficit_ticks[i] > CO_DESTROY_FACTORY_TICKS) destroyFactoryFromCompany(company, i--); // i-- to redo the newly missed factory otherwise
		else processTickFactory(company->controlled_factories[i]);
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
