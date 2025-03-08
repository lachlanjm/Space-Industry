#ifndef SAVE_FILE_STANDARDS_H
#define SAVE_FILE_STANDARDS_H

#define SAVE_FILE_SEP '='
#define SAVE_FILE_PTR_PREFIX '>'
#define SAVE_FILE_ID_SEP '_'
#define SAVE_FILE_ATTR_ID '\t'
#define SAVE_FILE_NEXT_ATTR_SEP '\n'
#define SAVE_FILE_ARR_ITEM_SEP ';'

#define SAVE_FILE_APP_STATE_ID "AppState"
#define SAVE_FILE_COMPANY_ID "Company"
#define SAVE_FILE_FACTORY_ID "Factory"
#define SAVE_FILE_GOVERNMENT_ID "Government"
#define SAVE_FILE_HISTORY_ARRAY_ID "HistoryArray"
#define SAVE_FILE_HISTORY_ARRAY_AVG_ID "HistoryArrayAvg"
#define SAVE_FILE_HISTORY_WTD_AVG_ARRAY_ID "HistoryWtdAvgArray"
#define SAVE_FILE_LOCAL_POPULATION_ID "LocalPopulation"
#define SAVE_FILE_LOGISTICS_CONTRACT_ID "LogisticsContract"
#define SAVE_FILE_LOGISTICS_MANAGER_ID "LogisticsManager"
#define SAVE_FILE_ORDER_ID "Order"
#define SAVE_FILE_PRODUCT_MARKET_ID "ProductMarket"
#define SAVE_FILE_STOCKPILE_ID "Stockpile"
#define SAVE_FILE_VEHICLE_ID "Vehicle"

#define SAVE_FILE_AS_LOG_MAN_NUM "logistics_managers_num"
#define SAVE_FILE_AS_LOG_MAN_ID "logistics_managers"
#define SAVE_FILE_AS_CO_NUM "companies_num"
#define SAVE_FILE_AS_CO_ID "companies"
#define SAVE_FILE_AS_GOV_NUM "governments_num"
#define SAVE_FILE_AS_GOV_ID "governments"
#define SAVE_FILE_AS_LOC_POP_NUM "local_population_num"
#define SAVE_FILE_AS_LOC_POP_ID "local_population"
#define SAVE_FILE_AS_MAR_BUY_AVG_ID "market_buy_avg"
#define SAVE_FILE_AS_MAR_SELL_AVG_ID "market_sell_avg"

#define SAVE_FILE_CO_WTH_ID "wealth"
#define SAVE_FILE_CO_CON_FAC_ID "controlled_factories"

#define SAVE_FILE_FAC_PRO_REC_ID "productionRecipe"
#define SAVE_FILE_FAC_STO_IN_ID "stockpiles_in"
#define SAVE_FILE_FAC_STO_OUT_ID "stockpiles_out"
#define SAVE_FILE_FAC_STO_IN_MAX_ID "stockpiles_in_max_quant"
#define SAVE_FILE_FAC_STO_OUT_MAX_ID "stockpiles_out_max_quant"
#define SAVE_FILE_FAC_ORD_IN_ID "orders_in"
#define SAVE_FILE_FAC_ORD_OUT_ID "orders_out"
#define SAVE_FILE_FAC_ORD_NUM_IN_ID "ordered_in"
#define SAVE_FILE_FAC_ORD_NUM_OUT_ID "ordered_out"

#define SAVE_FILE_FAC_LOC_ID "location"
#define SAVE_FILE_FAC_MAN_ID "management"
#define SAVE_FILE_FAC_MAN_TYP_ID "managementType"
#define SAVE_FILE_FAC_PRO_SPE_ID "processing_speed"
#define SAVE_FILE_FAC_LEF_PRO_ID "leftover_production"
#define SAVE_FILE_FAC_EMP_WAG_ID "employee_wages"
#define SAVE_FILE_FAC_CUR_EMP_ID "current_employee_num"
#define SAVE_FILE_FAC_MAX_EMP_ID "max_employee_num"
#define SAVE_FILE_FAC_PFT_HIS_ID "profit_history"

#define SAVE_FILE_GOV_WTH_ID "wealth"
#define SAVE_FILE_GOV_CTL_LOC_ID "controlled_location"
#define SAVE_FILE_GOV_GST_ID "gst_rate"
#define SAVE_FILE_GOV_CON_SPE_NEX_ID "consumption"
#define SAVE_FILE_GOV_IMP_ID "import_rate"
#define SAVE_FILE_GOV_EXP_ID "export_rate"
#define SAVE_FILE_GOV_BUY_AVG_ID "buy_avg"
#define SAVE_FILE_GOV_SELL_AVG_ID "sell_avg"

#define SAVE_FILE_HIS_ARR_ITEM_ID "value"

#define SAVE_FILE_HIS_ARR_AVG_ITEM_ID "value"

#define SAVE_FILE_HIS_WTD_AVG_ARR_VALUE_ID "value"
#define SAVE_FILE_HIS_WTD_AVG_ARR_WEIGHT_ID "weight"
#define SAVE_FILE_HIS_WTD_AVG_ARR_AVG_ID "average"

#define SAVE_FILE_LOC_POP_WTH_ID "wealth"
#define SAVE_FILE_LOC_POP_POP_NUM_ID "population_number"

#define SAVE_FILE_LOC_POP_POP_CEN_ID "population_centre"

#define SAVE_FILE_LOG_MAN_WTH_ID "wealth"
#define SAVE_FILE_LOG_MAN_HQ_LOC_ID "headquarters_location"
#define SAVE_FILE_LOG_MAN_VEH_NUM "vehicles_num"
#define SAVE_FILE_LOG_MAN_VEH_ID "vehicles"
#define SAVE_FILE_LOG_MAN_CON_NUM "contracts_num"
#define SAVE_FILE_LOG_MAN_CON_ID "contracts"

#define SAVE_FILE_LOG_CON_VEH_ID "assigned_vehicle"
#define SAVE_FILE_LOG_CON_SEL_FAC_ID "selling_factory"
#define SAVE_FILE_LOG_CON_BUY_FAC_ID "buying_factory"
#define SAVE_FILE_LOG_CON_CUR_PHA_ID "current_phase"
#define SAVE_FILE_LOG_CON_PRO_ID "product"
#define SAVE_FILE_LOG_CON_QUA_ID "quantity"

#define SAVE_FILE_ORD_OFF_FAC_ID "offering_factory"
#define SAVE_FILE_ORD_OFF_NUM_ID "offer_num"
#define SAVE_FILE_ORD_PRI_ID "price"

#define SAVE_FILE_PRO_MAR_LOC_ID "location"
#define SAVE_FILE_PRO_MAR_PRO_ID "product"
#define SAVE_FILE_PRO_MAR_SELL_HIS_ID "sell_hist_arr"
#define SAVE_FILE_PRO_MAR_BUY_HIS_ID "buy_hist_arr"

#define SAVE_FILE_STO_PRO_ID "product_type"
#define SAVE_FILE_STO_QUA_ID "quantity"
#define SAVE_FILE_STO_QUA_HIS_ID "quantity_history"

#define SAVE_FILE_VEH_STO_ID "stockpile"

#define SAVE_FILE_VEH_CUR_LOC_ID "current_location"
#define SAVE_FILE_VEH_END_LOC_ID "end_location"
#define SAVE_FILE_VEH_DIS_TRA_ID "distance_travelled"
#define SAVE_FILE_VEH_END_FAC_ID "end_factory"
#define SAVE_FILE_VEH_MAX_CAP_ID "max_capacity"

#define BUF_SIZE 128

enum AttributeTypes {
	APP_STATE_SAVE,
	COMPANY_SAVE,
	FACTORY_SAVE,
	GOVERNMENT_SAVE,
	HISTORY_ARRAY_SAVE,
	HISTORY_ARRAY_AVG_SAVE,
	HISTORY_WTD_AVG_ARRAY_SAVE,
	LOCAL_POPULATION_SAVE,
	LOGISTICS_CONTRACT_SAVE,
	LOGISTICS_MANAGER_SAVE,
	ORDER_SAVE,
	PRODUCT_MARKET_SAVE,
	STOCKPILE_SAVE,
	VEHICLE_SAVE,
	STRUCT_SAVE_NUM
};

#endif