#include "Government.h"

static int government_count = 0;
static Government* __static_government_arr = NULL;

static int location_count = 0;
static Government** __static_government_control = NULL;

void setGovernmentCountStatic(const int _government_count)
{
	__static_government_arr = (Government*) calloc(_government_count, sizeof(Government));
	government_count = _government_count;
	for (int i = 0; i < government_count; i++)
	{
		assignGovernmentValues(&__static_government_arr[i], 3000);
	}
}

int getGovernmentNum(void)
{
	return government_count;
}

Government* getGovernmentByIndex(const int index)
{
	return &__static_government_arr[index];
}

void setGovernmentControlStatic(const int transport_node_count)
{
	__static_government_control = (Government**) calloc(transport_node_count, sizeof(Government*));
	location_count = transport_node_count;
}

Government* getGovernmentByLocation(const TransportNode location)
{
	return __static_government_control[location];
}

void setGovernmentControlByLocation(Government* government, const TransportNode location)
{
	if (__static_government_control[location] != NULL) 
	{
		__static_government_control[location]->controlled_local_population_num--;
	}
	__static_government_control[location] = government;
	government->controlled_local_population_num++;
}

void resetGovernmentControlByLocation(const TransportNode location)
{
	if (__static_government_control[location] != NULL) 
	{
		__static_government_control[location]->controlled_local_population_num--;
	}
	__static_government_control[location] = NULL;
}

void cleanGovernmentStatic(void)
{
	for (int i = 0; i < government_count; i++)
	{
		cleanGovernment(&__static_government_arr[i]);
	}

	if (__static_government_arr != NULL)
	{
		free(__static_government_arr);
	}
	__static_government_arr = NULL;
	government_count = 0;

	if (__static_government_control != NULL)
	{
		free(__static_government_control);
	}
	__static_government_control = NULL;
	location_count = 0;
}

// TODO allow for product specific taxes
int32_t getExportTaxRate(const Product product, const TransportNode from, const TransportNode to)
{
	const int to_index = (__static_government_control[to] - __static_government_arr) / sizeof(Government);
	return __static_government_control[from]->export_tariffs[to_index];
}

// TODO allow for product specific taxes
int32_t getGstTaxRate(const Product product, const TransportNode location)
{
	return __static_government_control[location]->gst_rate;
}

// TODO allow for product specific taxes
int32_t getImportTaxRate(const Product product, const TransportNode from, const TransportNode to)
{
	const int from_index = (__static_government_control[from] - __static_government_arr) / sizeof(Government);
	return __static_government_control[to]->import_tariffs[from_index];
}

static GOVERNMENT_ID_INT id_next = 0;
void assignGovernmentValues(Government* government, const int wealth)
{
	government->wealth = wealth;
	government->controlled_local_population_num = 0;

	government->gst_rate = 5000; // 5%

	if (government->import_tariffs != NULL)
	{
		free(government->import_tariffs);
	}
	government->import_tariffs = (int*) calloc(government_count, sizeof(int));

	if (government->export_tariffs != NULL)
	{
		free(government->export_tariffs);
	}
	government->export_tariffs = (int*) calloc(government_count, sizeof(int));
	
	for (int i=0; i<government_count; i++)
	{
		if (&__static_government_arr[i] == government)
		{
			government->import_tariffs[i] = 0;
			government->export_tariffs[i] = 0;
		}
		else
		{
			government->import_tariffs[i] = 1000; // 1%
			government->export_tariffs[i] = 1000; // 1%
		}
	}

	if (government->gov_market_buy_avg != NULL) free(government->gov_market_buy_avg);
	government->gov_market_buy_avg = (HistoryWtdAvgArray*) calloc(PRODUCT_COUNT, sizeof(HistoryWtdAvgArray));

	if (government->gov_market_sell_avg != NULL) free(government->gov_market_sell_avg);
	government->gov_market_sell_avg = (HistoryWtdAvgArray*) calloc(PRODUCT_COUNT, sizeof(HistoryWtdAvgArray));

	for (int i = 0; i < PRODUCT_COUNT; i++)
	{
		assignHistoryWtdAvgArrayValues(&government->gov_market_buy_avg[i]);
		assignHistoryWtdAvgArrayValues(&government->gov_market_sell_avg[i]);
	}

	government->id = id_next++;
}

void assignLoadIdGovernment(Government* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void recordGovMarketProductBuyPrice(Government* const government, const Product product, const QUANTITY_INT quantity, const int price)
{
	if (product >= PRODUCT_COUNT) return;
	if (quantity < 0) return;
	addToHistoryWtdAvgArray(&government->gov_market_buy_avg[product], quantity * price, quantity);
}

void recordGovMarketProductSellPrice(Government* const government, const Product product, const QUANTITY_INT quantity, const int price)
{
	if (product >= PRODUCT_COUNT) return;
	if (quantity < 0) return;
	addToHistoryWtdAvgArray(&government->gov_market_sell_avg[product], quantity * price, quantity);
}

int getGovMarketBuyAvgByProduct(const Government* const government, const Product product)
{
	if (product >= PRODUCT_COUNT) return -1;
	return getAvgHistoryWtdAvgArray(&government->gov_market_buy_avg[product]);
}

int getGovMarketSellAvgByProduct(const Government* const government, const Product product)
{
	if (product >= PRODUCT_COUNT) return -1;
	return getAvgHistoryWtdAvgArray(&government->gov_market_sell_avg[product]);
}

HistoryWtdAvgArray* getGovMarketBuyHistoryWtdAvgArrByProduct(const Government* const government, const Product product)
{
	return &government->gov_market_buy_avg[product];
}

HistoryWtdAvgArray* getGovMarketSellHistoryWtdAvgArrByProduct(const Government* const government, const Product product)
{
	return &government->gov_market_sell_avg[product];
}

void insertFundsGovernment(Government* government, const int funds)
{
	government->wealth += funds;
}

void withdrawFundsGovernment(Government* government, const int funds)
{
	if (government->wealth < funds) return; // reject payment
	government->wealth -= funds;
}

void processTickAllGovernments(void)
{
	for (int i = 0; i < government_count; i++)
	{
		processTickGovernment(&__static_government_arr[i]);
	}
}

// TODO optimise runtime
void processTickGovernment(Government* government)
{
	const int welfare_payments = government->wealth / government->controlled_local_population_num;
	for (TransportNode curr_loc = 0; curr_loc<location_count;curr_loc++)
	{
		if (government == getGovernmentByLocation(curr_loc))
		{
			withdrawFundsGovernment(government, welfare_payments);
			insertFundsLocalPopulation(
				getLocalPopulationByLocation(curr_loc),
				welfare_payments
			);
		}
	}
	for (int i = 0; i < PRODUCT_COUNT; i++)
	{
		tickHistoryWtdAvgArrayIndex(&government->gov_market_buy_avg[i]);
		tickHistoryWtdAvgArrayIndex(&government->gov_market_sell_avg[i]);
	}
}

void cleanGovernment(Government* government)
{
	if (government->import_tariffs != NULL)
	{
		free(government->import_tariffs);
		government->import_tariffs = NULL;
	}
	if (government->export_tariffs != NULL)
	{
		free(government->export_tariffs);
		government->export_tariffs = NULL;
	}
	if (government->gov_market_buy_avg != NULL)
	{
		free(government->gov_market_buy_avg);
		government->gov_market_buy_avg = NULL;
	}
	if (government->gov_market_sell_avg != NULL)
	{
		free(government->gov_market_sell_avg);
		government->gov_market_sell_avg = NULL;
	}
}
