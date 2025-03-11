#include "LogisticsManager.h"

static LOGISTICS_MANAGER_ID_INT id_next = 0;

LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num, const TransportNode headquarters_location)
{
	LogisticsManager* logisticsManager = (LogisticsManager*) calloc(1, sizeof(LogisticsManager));
	assignLogisticsManagerValues(logisticsManager, vehicles_num, headquarters_location);
	return logisticsManager;
}

void assignLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num, const TransportNode headquarters_location)
{	
	logisticsManager->vehicles_num = vehicles_num;

	if (logisticsManager->vehicles_num > 0)
	{
		logisticsManager->vehicles = calloc(logisticsManager->vehicles_num, sizeof(Vehicle*));
	}
	else
	{
		logisticsManager->vehicles = NULL;
	}

	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		logisticsManager->vehicles[i] = newVehicle(headquarters_location);
	}

	logisticsManager->contracts_num = 0;
	logisticsManager->contracts = NULL;

	logisticsManager->headquarters_location = headquarters_location;
	logisticsManager->wealth = 100000;

	logisticsManager->id = id_next++;
}

LogisticsContract* addNewLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle, Factory* selling_factory, Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
	logisticsManager->contracts = realloc(logisticsManager->contracts, ++logisticsManager->contracts_num * sizeof(LogisticsContract));
	const LogisticsContract* new_contract = &logisticsManager->contracts[logisticsManager->contracts_num-1];
	memset(new_contract, 0, sizeof(LogisticsContract));
	addOrderedOutQuantity(selling_factory, product, quantity);
	addOrderedInQuantity(buying_factory, product, quantity);
	assignLogisticsContractValues(new_contract, vehicle, selling_factory, buying_factory, ASSIGNMENT, product, quantity);
	return new_contract;
}

void loadLogisticsManagerConstructorLogisticsContract(LogisticsManager* logisticsManager, const uint_fast16_t contracts_num)
{
	logisticsManager->contracts_num = contracts_num;
	if (logisticsManager->contracts) free(logisticsManager->contracts);
	logisticsManager->contracts = (LogisticsContract*) calloc(contracts_num, sizeof(LogisticsContract));
}

void assignLoadIdLogisticsManager(LogisticsManager* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void addVehicleToLogisticsManager(LogisticsManager* const logisticsManager)
{
	if (logisticsManager->vehicles_num++ == 0)
	{
		logisticsManager->vehicles = calloc(1, sizeof(Vehicle*));
	}
	else
	{
		logisticsManager->vehicles = realloc(logisticsManager->vehicles, logisticsManager->vehicles_num * sizeof(Vehicle*));
	}
	logisticsManager->vehicles[logisticsManager->vehicles_num-1] = newVehicle(logisticsManager->headquarters_location);
}

void insertFundsLogisticsManager(LogisticsManager* logisticsManager, const int funds)
{
	logisticsManager->wealth += funds;
}
void withdrawFundsLogisticsManager(LogisticsManager* logisticsManager, const int funds)
{
	if (logisticsManager->wealth < funds) return; // reject payment
	logisticsManager->wealth -= funds;
}

static double __dist_to_profit_eff__[TRANSPORT_NODE_COUNT][TRANSPORT_NODE_COUNT][PRODUCT_COUNT];
static inline void calculate_route_profit(const int from, const ProductMarket* const from_market, const int to, const ProductMarket* const to_market, const int product)
{
	if (to_market->buy_order_num > 0
		&& from_market->sell_order_num > 0)
	{
		const int_fast64_t export_price = from_market->sell_order_arr[0]->price;
		const int_fast64_t export_tax = (double)export_price * (
			(double)getExportTaxRate(product, from, to) 
			/ 100000.0f
		);

		const int_fast64_t import_price = to_market->buy_order_arr[0]->price;
		const int_fast64_t import_tax = (double)import_price * (
			(double)(getGstTaxRate(product, to)
			+ getImportTaxRate(product, from, to)) 
			/ 100000.0f
		);

		const double profit = (double) (import_price - import_tax - export_price - export_tax);
		const double quantity = (double) MIN(from_market->sell_order_arr[0]->offer_num, to_market->buy_order_arr[0]->offer_num);
		
		if (getTotalDistance(from, to) == 0)
			__dist_to_profit_eff__[from][to][product] = profit * quantity;
		else 
			__dist_to_profit_eff__[from][to][product] = (profit / (double)getTotalDistance(from, to)) * quantity;
		
	}
	else
		__dist_to_profit_eff__[from][to][product] = 0;
}

void update_dist_to_profit_eff(void)
{
	for (int product = 0; product < PRODUCT_COUNT; product++)
	{
		for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
		{
			const ProductMarket* const from_market = getProductMarketAtLocation(from, product);
			for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
			{
				calculate_route_profit(from, from_market, to, getProductMarketAtLocation(to, product), product);
			}
		}
	}
}

static inline void update_dist_to_profit_eff_product_filtered(int product)
{
	for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
	{
		const ProductMarket* const from_market = getProductMarketAtLocation(from, product);
		for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
		{
			calculate_route_profit(from, from_market, to, getProductMarketAtLocation(to, product), product);
		}
	}
}

LogisticsContract* assignLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle)
{
	int from_max = -1;
	int to_max = -1;
	int product_max = -1;
	double eff_max = 0;

	double eff = 0;
	int dist_to = 0;

	for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
	{
		for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
		{
			for (int product = 0; product < PRODUCT_COUNT; product++)
			{
				eff = __dist_to_profit_eff__[from][to][product];
				dist_to = getTotalDistance(vehicle->current_location, from);
				if (dist_to != 0) eff /= (double) dist_to;

				if (eff > eff_max)
				{
					from_max = from;
					to_max = to;
					product_max = product;
					eff_max = eff;
				}
			}
		}
	}

	if (from_max == -1)
	{
		return NULL;
	}

	// TODO !!!! IMPROVE FLOW AND MEMORY ASSIGNMENT
	Factory* selling_factory = getProductMarketAtLocation(from_max, product_max)->sell_order_arr[0]->offering_factory;
	Factory* buying_factory = getProductMarketAtLocation(to_max, product_max)->buy_order_arr[0]->offering_factory;

	QUANTITY_INT quantity = match_orders(
		logisticsManager,
		getProductMarketAtLocation(from_max, product_max), 
		getProductMarketAtLocation(from_max, product_max)->sell_order_arr[0],
		getProductMarketAtLocation(to_max, product_max),
		getProductMarketAtLocation(to_max, product_max)->buy_order_arr[0]
	);

	const LogisticsContract* const new_contract = addNewLogisticsContract(
		logisticsManager,
		vehicle,
		selling_factory,
		buying_factory,
		product_max,
		quantity
	);

	update_dist_to_profit_eff_product_filtered(product_max);
	return new_contract;
}

static inline void assignFreeVehicles(LogisticsManager* const logisticsManager)
{
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		if (logisticsManager->vehicles[i]->end_location == -1)
		{
			const LogisticsContract* new_contract = assignLogisticsContract(logisticsManager, logisticsManager->vehicles[i]);
			if (new_contract) processTickLogisticsContract(new_contract); // Completes the ASSIGNMENT phase
			else return;
		}
	}
}

void processTickLogisticsManager(LogisticsManager* const logisticsManager)
{
	if (logisticsManager->wealth >= LOGISTICS_MANAGER_NEW_VEHICLE_COST
		&& ((float)logisticsManager->contracts_num / (float)logisticsManager->vehicles_num) >= (1-LOGISTICS_MANAGER_DESIRED_FREE_VEHICLE_FACTOR))
	{
		addVehicleToLogisticsManager(logisticsManager);	
		// TODO TBU
		withdrawFundsLogisticsManager(logisticsManager, LOGISTICS_MANAGER_NEW_VEHICLE_COST);
		insertFundsGovernment(
			getGovernmentByLocation(logisticsManager->headquarters_location),
			LOGISTICS_MANAGER_NEW_VEHICLE_COST
		);
	}
	else if (logisticsManager->wealth >= LOGISTICS_MANAGER_MAX_WEALTH_DONATION_TRIGGER * LOGISTICS_MANAGER_NEW_VEHICLE_COST)
	{
		// TODO TBU
		const int wealth = logisticsManager->wealth;
		withdrawFundsLogisticsManager(logisticsManager, wealth);
		insertFundsGovernment(
			getGovernmentByLocation(logisticsManager->headquarters_location),
			wealth
		);
	}
}

void processTickLogisticsManagerContracts(LogisticsManager* const logisticsManager)
{
	// Search and add contracts
	assignFreeVehicles(logisticsManager);

	// Tick contracts
	for (int i = 0; i < logisticsManager->contracts_num; i++)
	{
		if(processTickLogisticsContract(&logisticsManager->contracts[i]))
		{
			logisticsManager->contracts_num--;
			for (int x = i; x < logisticsManager->contracts_num; x++)
			{
				logisticsManager->contracts[x] = logisticsManager->contracts[x + 1];
			}
			cleanContract(&logisticsManager->contracts[logisticsManager->contracts_num]);

			if (logisticsManager->contracts_num == 0)
			{
				free(logisticsManager->contracts);
				logisticsManager->contracts = NULL;
			}
			else
			{
				logisticsManager->contracts = realloc(logisticsManager->contracts, logisticsManager->contracts_num * sizeof(LogisticsContract));
			}
		}
	}
}

void processTickLogisticsManagerVehicles(const LogisticsManager* const logisticsManager)
{
	// Tick vehicles
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		processTickVehicle(logisticsManager->vehicles[i]);
	}
}

void cleanLogisticsManager(LogisticsManager* logisticsManager)
{
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		cleanVehicle(logisticsManager->vehicles[i]);
		free(logisticsManager->vehicles[i]);
	}
	free(logisticsManager->vehicles);

	for (int i = 0; i < logisticsManager->contracts_num; i++)
	{
		cleanContract(&logisticsManager->contracts[i]);
	}
	free(logisticsManager->contracts);
}

