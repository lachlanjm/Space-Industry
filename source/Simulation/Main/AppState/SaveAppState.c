#include "SaveAppState.h"

static struct SaveStateQueue* first_item;

static inline char* getSaveFormatName(char buffer[BUF_SIZE], const enum AttributeTypes attributeType, const int id)
{
	switch(attributeType)
	{
		case APP_STATE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_APP_STATE_ID);
			break;
		case COMPANY_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_COMPANY_ID);
			break;
		case FACTORY_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_FACTORY_ID);
			break;
		case GOVERNMENT_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_GOVERNMENT_ID);
			break;
		case HISTORY_ARRAY_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_HISTORY_ARRAY_ID);
			break;
		case HISTORY_ARRAY_AVG_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_HISTORY_ARRAY_AVG_ID);
			break;
		case HISTORY_WTD_AVG_ARRAY_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_HISTORY_WTD_AVG_ARRAY_ID);
			break;
		case LOCAL_POPULATION_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_LOCAL_POPULATION_ID);
			break;
		case LOGISTICS_CONTRACT_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_LOGISTICS_CONTRACT_ID);
			break;
		case LOGISTICS_MANAGER_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_LOGISTICS_MANAGER_ID);
			break;
		case ORDER_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_ORDER_ID);
			break;
		case PRODUCT_MARKET_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_PRODUCT_MARKET_ID);
			break;
		case STOCKPILE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_STOCKPILE_ID);
			break;
		case VEHICLE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_VEHICLE_ID);
			break;
		default:
			snprintf(buffer, BUF_SIZE, "%s", "Default");
			break;
	}
	snprintf(buffer, BUF_SIZE, "%.*s%c%d", BUF_SIZE - 5, buffer, SAVE_FILE_ID_SEP, id);
	return buffer;
}

static inline char* getSaveFormatPtrString(char buffer[BUF_SIZE], const enum AttributeTypes attributeType, const int id)
{
	char buffer_2[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%c%.*s", SAVE_FILE_PTR_PREFIX, BUF_SIZE - 2, getSaveFormatName(buffer_2, attributeType, id));
	return buffer;
}

static inline char* getSaveFormatStringAttribute(char buffer[BUF_SIZE], const char* attribute_name, const char* str)
{
	snprintf(buffer, BUF_SIZE, "%s%c%.*s", attribute_name, SAVE_FILE_SEP, BUF_SIZE - 20, str);
	return buffer;
}

static inline char* getSaveFormatIntegerAttribute(char buffer[BUF_SIZE], const char* attribute_name, const int integer)
{
	snprintf(buffer, BUF_SIZE, "%s%c%d", attribute_name, SAVE_FILE_SEP, integer);
	return buffer;
}

static inline char* getSaveFormatUnsignedIntegerAttribute(char buffer[BUF_SIZE], const char* attribute_name, const uint_least64_t u_integer)
{
	snprintf(buffer, BUF_SIZE, "%s%c%i", attribute_name, SAVE_FILE_SEP, u_integer);
	return buffer;
}

static inline char* getSaveFormatFloatAttribute(char buffer[BUF_SIZE], const char* attribute_name, const float float_val)
{
	snprintf(buffer, BUF_SIZE, "%s%c%f", attribute_name, SAVE_FILE_SEP, float_val);
	return buffer;
}

static inline char* getSaveFormatPointerAttribute(char buffer[BUF_SIZE], const char* attribute_name, const enum AttributeTypes attributeType, const int id)
{
	char buffer_2[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%s%c%.*s", attribute_name, SAVE_FILE_SEP, BUF_SIZE - 20, getSaveFormatPtrString(buffer_2, attributeType, id));
	return buffer;
}

static inline int writeToFile(FILE* fptr, const enum WriteType write_func, const char* str)
{
	switch (write_func)
	{
		case NEW_STRUCT_WRITE:
			return fprintf(fptr, "%s%c", str, SAVE_FILE_NEXT_ATTR_SEP);
		case ADD_ATTRIBUTE_WRITE:
			return fprintf(fptr, "%c%s%c", SAVE_FILE_ATTR_ID, str, SAVE_FILE_NEXT_ATTR_SEP);
		case BLANK_LINE:
			return fprintf(fptr, "%c", SAVE_FILE_NEXT_ATTR_SEP);
		default:
			return fprintf(fptr, "%s%c", str, SAVE_FILE_NEXT_ATTR_SEP);
	}
}

static inline struct SaveStateQueue* createQueue(AppState* appState)
{
	struct SaveStateQueue* item = calloc(1, sizeof(struct SaveStateQueue));

	item->type = APP_STATE_SAVE;
	item->data = appState;
	item->next = NULL;

	return item;
}

static inline void appendToQueue(enum AttributeTypes type, void* data)
{
	struct SaveStateQueue* base_item = first_item;
	while (base_item->next != NULL)
	{
		base_item = base_item->next;
	}
	base_item->next = calloc(1, sizeof(struct SaveStateQueue));

	base_item = base_item->next;
	base_item->type = type;
	base_item->data = data;
	base_item->next = NULL;
}

static inline void cleanUpQueue()
{
	struct SaveStateQueue* current_item = first_item;
	while (current_item->next != NULL)
	{
		current_item = current_item->next;
		free(first_item);
		first_item = current_item;
	}
	free(first_item);
}

static inline void saveAppStateFormat(FILE* fptr, AppState* appState)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, APP_STATE_SAVE, 0));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_AS_LOG_MAN_NUM, appState->logistics_managers_num)
	);
	for (int i = 0; i < appState->logistics_managers_num; i++)
	{
		appendToQueue(LOGISTICS_MANAGER_SAVE, &appState->logistics_managers[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_AS_LOG_MAN_ID, LOGISTICS_MANAGER_SAVE, appState->logistics_managers[i].id)
		);
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_AS_CO_NUM, appState->companies_num)
	);
	for (int i = 0; i < appState->companies_num; i++)
	{
		appendToQueue(COMPANY_SAVE, &appState->companies[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_AS_CO_ID, COMPANY_SAVE, appState->companies[i].id)
		);
	}

	// TODO: fix up to non-appstate location (config file)
	// Currently set to record the values as only place atm for this
	const int pop_num = getLocalPopulationNum();
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_AS_LOC_POP_NUM, pop_num)
	);
	for (int i = 0; i < pop_num; i++)
	{
		const LocalPopulation* pop = getLocalPopulationByLocation(i);
		appendToQueue(LOCAL_POPULATION_SAVE, pop);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_AS_LOC_POP_ID, LOCAL_POPULATION_SAVE, pop->id)
		);
	}

	// TODO make it adjust to var sizes
	for (int x=0; x<TRANSPORT_NODE_COUNT; x++)
	{
		for (int y=0; y<PRODUCT_COUNT; y++)
		{
			appendToQueue(PRODUCT_MARKET_SAVE, 
				getProductMarketAtLocation(x, y)
			);
		}
	}
	for (int i=0; i<PRODUCT_COUNT; i++)
	{
		HistoryWtdAvgArray* wtd_arr = getMarketBuyHistoryWtdAvgArrByProduct(i);
		appendToQueue(HISTORY_WTD_AVG_ARRAY_SAVE, wtd_arr);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_AS_MAR_BUY_AVG_ID, HISTORY_WTD_AVG_ARRAY_SAVE, wtd_arr->id)
		);
	}
	for (int i=0; i<PRODUCT_COUNT; i++)
	{
		HistoryWtdAvgArray* wtd_arr = getMarketSellHistoryWtdAvgArrByProduct(i);
		appendToQueue(HISTORY_WTD_AVG_ARRAY_SAVE, wtd_arr);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_AS_MAR_SELL_AVG_ID, HISTORY_WTD_AVG_ARRAY_SAVE, wtd_arr->id)
		);
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_AS_GOV_NUM, getGovernmentNum())
	);
	for (int i=0; i<getGovernmentNum(); i++)
	{
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_AS_GOV_ID, GOVERNMENT_SAVE, getGovernmentByIndex(i)->id)
		);
		appendToQueue(GOVERNMENT_SAVE, getGovernmentByIndex(i));
	}
}

static inline void saveCompany(FILE* fptr, Company* company)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, COMPANY_SAVE, company->id));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_CO_WTH_ID, company->wealth)
	);
	for (int i = 0; i < company->controlled_factories_num; i++)
	{
		appendToQueue(FACTORY_SAVE, company->controlled_factories[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_CO_CON_FAC_ID, FACTORY_SAVE, company->controlled_factories[i]->id)
		);
	}
}

static inline void saveFactory(FILE* fptr, Factory* factory)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, FACTORY_SAVE, factory->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_FAC_PRO_REC_ID, factory->productionRecipe)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_FAC_LOC_ID, factory->location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_FAC_MAN_TYP_ID, factory->managementType)
	);
	switch (factory->managementType)
	{
	case MANAGEMENT_COMPANY:
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_MAN_ID, COMPANY_SAVE, ((Company*)factory->management)->id)
		);
		break;
	case MANAGEMENT_LOCAL_POPULATION:
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_MAN_ID, LOCAL_POPULATION_SAVE, ((LocalPopulation*)factory->management)->id)
		);
		break;
	default:
		break;
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_PRO_SPE_ID, factory->processing_speed)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatFloatAttribute(buffer, SAVE_FILE_FAC_LEF_PRO_ID, factory->leftover_production)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_EMP_WAG_ID, factory->employee_wages)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_CUR_EMP_ID, factory->current_employee_num)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_MAX_EMP_ID, factory->max_employee_num)
	);

	appendToQueue(HISTORY_ARRAY_AVG_SAVE, &factory->profit_history);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_PFT_HIS_ID, HISTORY_ARRAY_AVG_SAVE, factory->profit_history.id)
	);

	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		appendToQueue(STOCKPILE_SAVE, &factory->stockpiles_in[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_STO_IN_ID, STOCKPILE_SAVE, factory->stockpiles_in[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_STO_IN_MAX_ID, factory->stockpiles_in_max_quant[i])
		);
		appendToQueue(ORDER_SAVE, &factory->orders_in[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_ORD_IN_ID, ORDER_SAVE, factory->orders_in[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_ORD_NUM_IN_ID, factory->ordered_in[i])
		);
	}

	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		appendToQueue(STOCKPILE_SAVE, &factory->stockpiles_out[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_STO_OUT_ID, STOCKPILE_SAVE, factory->stockpiles_out[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_STO_OUT_MAX_ID, factory->stockpiles_out_max_quant[i])
		);
		appendToQueue(ORDER_SAVE, &factory->orders_out[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_FAC_ORD_OUT_ID, ORDER_SAVE, factory->orders_out[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_FAC_ORD_NUM_OUT_ID, factory->ordered_out[i])
		);
	}
}

static inline void saveGovernment(FILE* fptr, Government* government)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, GOVERNMENT_SAVE, government->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_GOV_WTH_ID, government->wealth)
	);

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_GOV_GST_ID, government->gst_rate)
	);

	appendToQueue(HISTORY_ARRAY_AVG_SAVE, &government->consumption);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_GOV_CON_SPE_NEX_ID, HISTORY_ARRAY_AVG_SAVE, government->consumption.id)
	);

	for (int i = 0; i < getGovernmentNum(); i++)
	{
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatIntegerAttribute(buffer, SAVE_FILE_GOV_IMP_ID, government->import_tariffs[i])
		);
	}
	for (int i = 0; i < getGovernmentNum(); i++)
	{
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatIntegerAttribute(buffer, SAVE_FILE_GOV_EXP_ID, government->export_tariffs[i])
		);
	}

	for (int i = 0; i < TRANSPORT_NODE_COUNT; i++)
	{
		if (government == getGovernmentByLocation(i))
		{
			writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
				getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_GOV_CTL_LOC_ID, i)
			);
		}
	}

	for (int i = 0; i < PRODUCT_COUNT; i++)
	{
		appendToQueue(HISTORY_WTD_AVG_ARRAY_SAVE, &government->gov_market_buy_avg[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_GOV_BUY_AVG_ID, HISTORY_WTD_AVG_ARRAY_SAVE, government->gov_market_buy_avg[i].id)
		);
	}
	for (int i = 0; i < PRODUCT_COUNT; i++)
	{
		appendToQueue(HISTORY_WTD_AVG_ARRAY_SAVE, &government->gov_market_sell_avg[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_GOV_SELL_AVG_ID, HISTORY_WTD_AVG_ARRAY_SAVE, government->gov_market_sell_avg[i].id)
		);
	}
}

static inline void saveHistoryArray(FILE* fptr, HistoryArray* historyArray)
{
	static HistoryIterator* hist_iter;
	static HISTORY_INT history_value;

	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, HISTORY_ARRAY_SAVE, historyArray->id));

	hist_iter = newHistoryIterator(historyArray, HISTORY_ARRAY_TYPE);
	if (hist_iter)
	{
		while (getNextHistoryIterItem(hist_iter, &history_value)) 
		{
			writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
				getSaveFormatIntegerAttribute(buffer, SAVE_FILE_HIS_ARR_ITEM_ID, history_value)
			);
		}

		closeHistoryIterator(hist_iter);
	}
}

static inline void saveHistoryArrayAvg(FILE* fptr, HistoryArrayAvg* historyArray)
{
	static HistoryIterator* hist_iter;
	static HISTORY_INT history_value;

	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, HISTORY_ARRAY_AVG_SAVE, historyArray->id));

	hist_iter = newHistoryIterator(historyArray, HISTORY_ARRAY_AVG_TYPE);
	if (hist_iter)
	{
		while (getNextHistoryIterItem(hist_iter, &history_value)) 
		{
			writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
				getSaveFormatIntegerAttribute(buffer, SAVE_FILE_HIS_ARR_AVG_ITEM_ID, history_value)
			);
		}

		closeHistoryIterator(hist_iter);
	}
}

static inline void saveHistoryWtdAvgArray(FILE* fptr, HistoryWtdAvgArray* historyArray)
{
	static HistoryIterator* hist_value_iter;
	static HistoryIterator* hist_weight_iter;
	static HistoryIterator* hist_avg_iter;
	static HISTORY_INT history_value;
	static HISTORY_INT history_weight;
	static HISTORY_INT history_avg;

	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, HISTORY_WTD_AVG_ARRAY_SAVE, historyArray->id));

	hist_value_iter = newHistoryIterator(historyArray, HISTORY_WTD_AVG_ARRAY_VALUE_TYPE);
	if (hist_value_iter == NULL) { return; }

	hist_weight_iter = newHistoryIterator(historyArray, HISTORY_WTD_AVG_ARRAY_WEIGHT_TYPE);
	if (hist_weight_iter == NULL) { closeHistoryIterator(hist_value_iter); return; }
	
	hist_avg_iter = newHistoryIterator(historyArray, HISTORY_WTD_AVG_ARRAY_AVG_TYPE);
	if (hist_avg_iter == NULL) { closeHistoryIterator(hist_value_iter); closeHistoryIterator(hist_weight_iter); return; }

	while (getNextHistoryIterItem(hist_value_iter, &history_value)) 
	{
		getNextHistoryIterItem(hist_weight_iter, &history_weight);
		getNextHistoryIterItem(hist_avg_iter, &history_avg);

		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatIntegerAttribute(buffer, SAVE_FILE_HIS_WTD_AVG_ARR_VALUE_ID, history_value)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatIntegerAttribute(buffer, SAVE_FILE_HIS_WTD_AVG_ARR_WEIGHT_ID, history_weight)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatIntegerAttribute(buffer, SAVE_FILE_HIS_WTD_AVG_ARR_AVG_ID, history_avg)
		);
	}

	closeHistoryIterator(hist_avg_iter);
	closeHistoryIterator(hist_weight_iter);
	closeHistoryIterator(hist_value_iter);
}

static inline void saveLocalPopulation(FILE* fptr, LocalPopulation* population)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, LOCAL_POPULATION_SAVE, population->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_LOC_POP_POP_NUM_ID, population->population_number)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_LOC_POP_WTH_ID, population->wealth)
	);

	appendToQueue(FACTORY_SAVE, &population->population_centre);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_LOC_POP_POP_CEN_ID, FACTORY_SAVE, population->population_centre.id)
	);
}

static inline void saveLogisticsContract(FILE* fptr, LogisticsContract* logisticsContract)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, LOGISTICS_CONTRACT_SAVE, logisticsContract->id));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_LOG_CON_VEH_ID, VEHICLE_SAVE, logisticsContract->assigned_vehicle->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_LOG_CON_SEL_FAC_ID, FACTORY_SAVE, logisticsContract->selling_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_LOG_CON_BUY_FAC_ID, FACTORY_SAVE, logisticsContract->buying_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_LOG_CON_CUR_PHA_ID, logisticsContract->current_phase)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_LOG_CON_PRO_ID, logisticsContract->product)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_LOG_CON_QUA_ID, logisticsContract->quantity)
	);
}

static inline void saveLogisticsManager(FILE* fptr, LogisticsManager* logisticsManager)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, LOGISTICS_MANAGER_SAVE, logisticsManager->id));
	
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_LOG_MAN_WTH_ID, logisticsManager->wealth)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_LOG_MAN_HQ_LOC_ID, logisticsManager->headquarters_location)
	);

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_LOG_MAN_VEH_NUM, logisticsManager->vehicles_num)
	);
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		appendToQueue(VEHICLE_SAVE, &logisticsManager->vehicles[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_LOG_MAN_VEH_ID, VEHICLE_SAVE, logisticsManager->vehicles[i].id)
		);
	}

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_LOG_MAN_CON_NUM, logisticsManager->contracts_num)
	);
	for (int i = 0; i < logisticsManager->contracts_num; i++)
	{
		appendToQueue(LOGISTICS_CONTRACT_SAVE, &logisticsManager->contracts[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_LOG_MAN_CON_ID, LOGISTICS_CONTRACT_SAVE, logisticsManager->contracts[i].id)
		);
	}
}

static inline void saveOrder(FILE* fptr, Order* order)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, ORDER_SAVE, order->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_ORD_OFF_FAC_ID, FACTORY_SAVE, order->offering_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_ORD_OFF_NUM_ID, order->offer_num)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_ORD_PRI_ID, order->price)
	);
}

static inline void saveProductMarket(FILE* fptr, ProductMarket* productMarket)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, PRODUCT_MARKET_SAVE, productMarket->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_PRO_MAR_LOC_ID, productMarket->location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_PRO_MAR_PRO_ID, productMarket->product_type)
	);

	appendToQueue(HISTORY_WTD_AVG_ARRAY_SAVE, &productMarket->sell_hist_array);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_PRO_MAR_SELL_HIS_ID, HISTORY_WTD_AVG_ARRAY_SAVE, productMarket->sell_hist_array.id)
	);

	appendToQueue(HISTORY_WTD_AVG_ARRAY_SAVE, &productMarket->buy_hist_array);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_PRO_MAR_BUY_HIS_ID, HISTORY_WTD_AVG_ARRAY_SAVE, productMarket->buy_hist_array.id)
	);
}

static inline void saveStockpile(FILE* fptr, Stockpile* stockpile)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, STOCKPILE_SAVE, stockpile->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_STO_PRO_ID, stockpile->product_type)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_STO_QUA_ID, stockpile->quantity)
	);

	appendToQueue(HISTORY_ARRAY_SAVE, &stockpile->quantity_history);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_STO_QUA_HIS_ID, HISTORY_ARRAY_SAVE, stockpile->quantity_history.id)
	);
}

static inline void saveVehicle(FILE* fptr, Vehicle* vehicle)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, VEHICLE_SAVE, vehicle->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_VEH_CUR_LOC_ID, vehicle->current_location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, SAVE_FILE_VEH_END_LOC_ID, vehicle->end_location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_VEH_DIS_TRA_ID, vehicle->distance_travelled)
	);

	appendToQueue(STOCKPILE_SAVE, &vehicle->stockpile);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, SAVE_FILE_VEH_STO_ID, STOCKPILE_SAVE, vehicle->stockpile.id)
	);

	if (vehicle->end_factory != NULL)
	{
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, SAVE_FILE_VEH_END_FAC_ID, FACTORY_SAVE, vehicle->end_factory->id)
		);
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, SAVE_FILE_VEH_MAX_CAP_ID, vehicle->max_capacity)
	);
}

static inline void saveNextStruct(FILE* fptr, struct SaveStateQueue* item)
{
	switch (item->type)
	{
		case APP_STATE_SAVE:
			saveAppStateFormat(fptr, (AppState*) item->data);
			break;
		case COMPANY_SAVE:
			saveCompany(fptr, (Company*) item->data);
			break;
		case FACTORY_SAVE:
			saveFactory(fptr, (Factory*) item->data);
			break;
		case GOVERNMENT_SAVE:
			saveGovernment(fptr, (Government*) item->data);
			break;
		case HISTORY_ARRAY_SAVE:
			saveHistoryArray(fptr, (HistoryArray*) item->data);
			break;
		case HISTORY_ARRAY_AVG_SAVE:
			saveHistoryArrayAvg(fptr, (HistoryArrayAvg*) item->data);
			break;
		case HISTORY_WTD_AVG_ARRAY_SAVE:
			saveHistoryWtdAvgArray(fptr, (HistoryWtdAvgArray*) item->data);
			break;
		case LOCAL_POPULATION_SAVE:
			saveLocalPopulation(fptr, (LocalPopulation*) item->data);
			break;
		case LOGISTICS_CONTRACT_SAVE:
			saveLogisticsContract(fptr, (LogisticsContract*) item->data);
			break;
		case LOGISTICS_MANAGER_SAVE:
			saveLogisticsManager(fptr, (LogisticsManager*) item->data);
			break;
		case ORDER_SAVE:
			saveOrder(fptr, (Order*) item->data);
			break;
		case PRODUCT_MARKET_SAVE:
			saveProductMarket(fptr, (ProductMarket*) item->data);
			break;
		case STOCKPILE_SAVE:
			saveStockpile(fptr, (Stockpile*) item->data);
			break;
		case VEHICLE_SAVE:
			saveVehicle(fptr, (Vehicle*) item->data);
			break;
		default:
			printf("Invalid struct type during save: %1.d\n", item->type);
			break;
	}
}

int saveAppState(AppState* appState, const char* app_dir_path, const char* save_file_name)
{
	// Save app state
	char save_file_path[BUF_SIZE];
	snprintf(save_file_path, BUF_SIZE, "%s\\saves\\%s", app_dir_path, save_file_name);
	// TODO !!!!!!!!!!!!!!! ADD SAVE FILE COLLISION HANDLING!!!

	// Queue creation
	first_item = createQueue(appState);
	struct SaveStateQueue* current_item = first_item;

	// File Writing
	FILE *fptr;
	fptr = fopen(save_file_path, "w");

	if (!fptr)
	{
		printf("Save file did not load");
		return 1;
	}
	
	while (current_item != NULL)
	{
		saveNextStruct(fptr, current_item);
		current_item = current_item->next;
		fflush(stdout);
	}

	fclose(fptr);
	cleanUpQueue();
	return 0;
}
