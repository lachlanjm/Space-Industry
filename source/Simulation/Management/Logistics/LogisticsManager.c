#include "LogisticsManager.h"

static LOGISTICS_MANAGER_ID_INT id_next = 0;

LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num)
{
	LogisticsManager* logisticsManager = (LogisticsManager*) calloc(1, sizeof(LogisticsManager));
	assignLogisticsManagerValues(logisticsManager, vehicles_num);
	return logisticsManager;
}

void assignLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num)
{
	logisticsManager->vehicles_num = vehicles_num;

	logisticsManager->vehicles = (Vehicle*) realloc(logisticsManager->vehicles, vehicles_num * sizeof(Vehicle));

	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		assignVehicleValues(&logisticsManager->vehicles[i], 0);
	}

	logisticsManager->contracts_num = 0;
	logisticsManager->contracts = NULL;
	logisticsManager->id = id_next++;
}

void addNewLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle, Factory* selling_factory, Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
	logisticsManager->contracts = realloc(logisticsManager->contracts, ++logisticsManager->contracts_num * sizeof(LogisticsContract));
	addOrderedOutQuantity(selling_factory, product, quantity);
	addOrderedInQuantity(buying_factory, product, quantity);
	assignLogisticsContractValues(&logisticsManager->contracts[logisticsManager->contracts_num - 1], vehicle, selling_factory, buying_factory, ASSIGNMENT, product, quantity);
}

void loadLogisticsManagerConstructorVehicles(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num)
{
	logisticsManager->vehicles_num = vehicles_num;
	if (logisticsManager->vehicles) free(logisticsManager->vehicles);
	logisticsManager->vehicles = (Vehicle*) calloc(vehicles_num, sizeof(Vehicle));
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

static float __dist_to_price_eff__[TRANSPORT_NODE_COUNT][TRANSPORT_NODE_COUNT][PRODUCT_COUNT];
void update_dist_to_price_eff()
{
	for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
	{
		for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
		{
			for (int product = 0; product < PRODUCT_COUNT; product++)
			{
				if (getProductMarketAtLocation(to, product)->buy_order_num > 0
					&& getProductMarketAtLocation(from, product)->sell_order_num > 0)
				{
					if (getTotalDistance(from, to) == 0)
					{
						__dist_to_price_eff__[from][to][product] =
						(float) (getProductMarketAtLocation(to, product)->buy_order_arr[0]->price 
						- getProductMarketAtLocation(from, product)->sell_order_arr[0]->price);
					}
					else 
					{
						__dist_to_price_eff__[from][to][product] =
						(float) (getProductMarketAtLocation(to, product)->buy_order_arr[0]->price 
						- getProductMarketAtLocation(from, product)->sell_order_arr[0]->price)
						/ (float)getTotalDistance(from, to);
					}
				}
				else
				{
					__dist_to_price_eff__[from][to][product] = 0;
				}
			}
		}
	}
}

void update_dist_to_price_eff_product_filtered(int product)
{
	for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
	{
		for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
		{
			if (getProductMarketAtLocation(to, product)->buy_order_num > 0
				&& getProductMarketAtLocation(from, product)->sell_order_num > 0)
			{
				if (getTotalDistance(from, to) == 0)
				{
					__dist_to_price_eff__[from][to][product] =
					(float) (getProductMarketAtLocation(to, product)->buy_order_arr[0]->price 
					- getProductMarketAtLocation(from, product)->sell_order_arr[0]->price);
				}
				else 
				{
					__dist_to_price_eff__[from][to][product] =
					(float) (getProductMarketAtLocation(to, product)->buy_order_arr[0]->price 
					- getProductMarketAtLocation(from, product)->sell_order_arr[0]->price)
					/ (float)getTotalDistance(from, to);
				}
			}
			else
			{
				__dist_to_price_eff__[from][to][product] = 0;
			}
		}
	}
}
	
void assignFreeVehicles(LogisticsManager* logisticsManager)
{
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		if (logisticsManager->vehicles[i].end_location == -1)
		{
			assignLogisticsContract(logisticsManager, &logisticsManager->vehicles[i]);
		}
	}
}

// TODO: return value to indicate no new state and stop iterating for current tick
void assignLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle)
{
	int from_max = -1;
	int to_max = -1;
	int product_max = -1;
	float eff_max = 0;

	float eff = 0;
	int dist_to = 0;

	for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
	{
		for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
		{
			for (int product = 0; product < PRODUCT_COUNT; product++)
			{
				eff = __dist_to_price_eff__[from][to][product];
				dist_to = getTotalDistance(vehicle->current_location, from);
				if (dist_to != 0) eff /= (float) dist_to;

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
		return;
	}

	// TODO !!!! IMPROVE FLOW AND MEMORY ASSIGNMENT
	Factory* selling_factory = getProductMarketAtLocation(from_max, product_max)->sell_order_arr[0]->offering_factory;
	Factory* buying_factory = getProductMarketAtLocation(to_max, product_max)->buy_order_arr[0]->offering_factory;

	QUANTITY_INT quantity = match_orders(
		getProductMarketAtLocation(from_max, product_max), 
		getProductMarketAtLocation(from_max, product_max)->sell_order_arr[0],
		getProductMarketAtLocation(to_max, product_max),
		getProductMarketAtLocation(to_max, product_max)->buy_order_arr[0]
	);

	addNewLogisticsContract(
		logisticsManager,
		vehicle,
		selling_factory,
		buying_factory,
		product_max,
		quantity
	);

	update_dist_to_price_eff_product_filtered(product_max);
}

void processTickLogisticsManagerContracts(LogisticsManager* logisticsManager)
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
			logisticsManager->contracts = realloc(logisticsManager->contracts, logisticsManager->contracts_num * sizeof(LogisticsContract));
		}
	}
}

void processTickLogisticsManagerVehicles(LogisticsManager* logisticsManager)
{
	// Tick vehicles
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		processTickVehicle(&logisticsManager->vehicles[i]);
	}
}

void cleanLogisticsManager(LogisticsManager* logisticsManager)
{
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		cleanVehicle(&logisticsManager->vehicles[i]);
	}
	free(logisticsManager->vehicles);

	for (int i = 0; i < logisticsManager->contracts_num; i++)
	{
		cleanContract(&logisticsManager->contracts[i]);
	}
	free(logisticsManager->contracts);
}

