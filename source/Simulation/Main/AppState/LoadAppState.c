#include "LoadAppState.h"

// LOADING OBJECT REPOSITORY
static struct LoadStateIdList* __object_arr = NULL;

// TMP OBJECT array
static int __lclpop_arr_num = 0;
static LocalPopulation* __lclpop_arr = NULL;

static inline int getNextDataPoint(FILE *fptr, char new_data_point[BUF_SIZE + 1])
{
	int i = 0;
	char new_char = fgetc(fptr);
	if (feof(fptr)) return 0;
	while (new_char != SAVE_FILE_NEXT_ATTR_SEP)
	{
		new_data_point[i++] = new_char;
		new_char = fgetc(fptr);
		if (feof(fptr)) return 0;
	}
	new_data_point[i] = '\0';
	return 1;
}

static inline enum AttributeTypes matchIdentifierWithType(const char* id)
{
	if (strcmp(id, SAVE_FILE_APP_STATE_ID) == 0)
	{
		return APP_STATE_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_COMPANY_ID) == 0)
	{
		return COMPANY_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_FACTORY_ID) == 0)
	{
		return FACTORY_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_GOVERNMENT_ID) == 0)
	{
		return GOVERNMENT_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_HISTORY_ARRAY_ID) == 0)
	{
		return HISTORY_ARRAY_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_HISTORY_ARRAY_AVG_ID) == 0)
	{
		return HISTORY_ARRAY_AVG_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_HISTORY_WTD_AVG_ARRAY_ID) == 0)
	{
		return HISTORY_WTD_AVG_ARRAY_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_LOCAL_POPULATION_ID) == 0)
	{
		return LOCAL_POPULATION_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_LOGISTICS_CONTRACT_ID) == 0)
	{
		return LOGISTICS_CONTRACT_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_LOGISTICS_MANAGER_ID) == 0)
	{
		return LOGISTICS_MANAGER_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_ORDER_ID) == 0)
	{
		return ORDER_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_PRODUCT_MARKET_ID) == 0)
	{
		return PRODUCT_MARKET_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_STOCKPILE_ID) == 0)
	{
		return STOCKPILE_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_VEHICLE_ID) == 0)
	{
		return VEHICLE_SAVE;
	}
	else
	{
		return -1;
	}
}

static inline int extractObjectId(char* ptr_string_id)
{
	int i = 0;
	while (ptr_string_id[i] != SAVE_FILE_ID_SEP)
	{
		if (ptr_string_id[i] == '\0')
		{
			return -1;
		}
		i++;
	}
	ptr_string_id[i++] = '\0'; // Removes the unnecessary data after
	int result = atoi(ptr_string_id + i);
	if (result == 0 && ptr_string_id[i] != '0')
	{
		return -1;
	}
	if (ptr_string_id[0] == SAVE_FILE_PTR_PREFIX)
	{
		sprintf(ptr_string_id, "%s", ptr_string_id + 1); // Remove PTR symbol
	}
	return result;
}

static inline void extractAttribute(char* new_data_point, char* attribute_value_buffer)
{
	int i = 0;
	while (new_data_point[i] != SAVE_FILE_SEP)
	{
		if (new_data_point[i] == '\0')
		{
			return;
		}
		i++;
	}
	new_data_point[i++] = '\0'; // Removes the unnecessary data after
	snprintf(attribute_value_buffer, BUF_SIZE, "%s", new_data_point + i);
}

static inline void addNewStructIdPtr(const enum AttributeTypes obj_type, const int id, const void* data)
{
	struct LoadStateIdList* base_item = &__object_arr[obj_type];

	if (base_item->data == NULL)
	{
		__object_arr[obj_type].data = data;
		__object_arr[obj_type].id = id;
		__object_arr[obj_type].next = NULL;
	}
	else
	{
		while (base_item->next)
		{
			base_item = base_item->next;
		}

		base_item->next = calloc(1, sizeof(struct LoadStateIdList));
		base_item->next->data = data;
		base_item->next->id = id;
		base_item->next->next = NULL;
	}
}

// Update ONLY the PTR such that the linked list and array share the same ordering and size of the pointers. 
// Requires an array of LocalPopulations. Expects at least and will only traverse up to the length of linked list,
static inline void updateLocalPopStructPtrsFromArr(const LocalPopulation* arr)
{
	struct LoadStateIdList* item = &__object_arr[LOCAL_POPULATION_SAVE];

	if (item == NULL) return;

	int i = 0;
	do
	{
		item->data = &arr[i++];
		item = item->next;
	} while (item);
}

static inline struct LoadStateIdList* getItemWithId(const struct LoadStateIdList* item, const int id)
{	
	while (item != NULL)
	{
		if (item->id == id) return item;
		item = item->next;
	}

	printf("Item not found; id=%i\n", id); fflush(stdout);
	return NULL;
}

static inline struct LoadStateIdList* getObject(const enum AttributeTypes obj_type, const int id)
{
	if (obj_type < 0 || STRUCT_SAVE_NUM <= obj_type) return NULL;
	return getItemWithId(&__object_arr[obj_type], id);
}

static inline void getNextObject(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList** current_obj_item)
{
	int id = extractObjectId(new_data_point);
	*current_obj_type = matchIdentifierWithType(new_data_point);
	*current_obj_item = getObject(*current_obj_type, id);
}

static int current_index = 0;
static char current_arr_name[BUF_SIZE] = "";
static TransportNode current_location;
static Product current_product;
static inline void addNewStructForPtrs(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList** current_obj_ptr)
{
	int id = extractObjectId(new_data_point);
	*current_obj_type = matchIdentifierWithType(new_data_point);
	if (*current_obj_type == APP_STATE_SAVE)
	{
		addNewStructIdPtr(*current_obj_type, id, calloc(1, sizeof(AppState)));

		// TODO make it adjust to var sizes and in the appState loading
		if (getProductMarketAtLocation(0,0) != NULL) cleanMarketMap();
		instantiateNewMarketMap(TRANSPORT_NODE_COUNT, PRODUCT_COUNT); // TODO TBU

		for (int x=0; x<TRANSPORT_NODE_COUNT; x++) // TODO TBU
		{
			for (int y=0; y<PRODUCT_COUNT; y++) // TODO TBU
			{
				// REALLY BAD USE OF ID - ERRORS?
				addNewStructIdPtr(PRODUCT_MARKET_SAVE, x*PRODUCT_COUNT+y, getProductMarketAtLocation(x, y));
			}
		}
	}
	*current_obj_ptr = getObject(*current_obj_type, id);
	current_index = 0;
	snprintf(current_arr_name, BUF_SIZE, "");
}

static inline void addNewAttributeForPtrs(char new_data_point[BUF_SIZE + 1], const enum AttributeTypes current_obj_type, struct LoadStateIdList* current_obj_ptr)
{
	char attr_value[BUF_SIZE];
	new_data_point++; // Removes SAVE_FILE_ATTR_ID char
	extractAttribute(new_data_point, attr_value);

	switch (current_obj_type)
	{
		case APP_STATE_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_AS_LOG_MAN_NUM) == 0)
			{
				int num = atoi(attr_value);
				((AppState*)current_obj_ptr->data)->logistics_managers_num = num;
				((AppState*)current_obj_ptr->data)->logistics_managers_next_process_tick_index = 0;
				((AppState*)current_obj_ptr->data)->logistics_managers = (LogisticsManager*) calloc(num, sizeof(LogisticsManager));
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_CO_NUM) == 0)
			{
				((AppState*)current_obj_ptr->data)->companies_num = atoi(attr_value);
				((AppState*)current_obj_ptr->data)->companies = (Company*) calloc(((AppState*)current_obj_ptr->data)->companies_num, sizeof(Company));
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_LOC_POP_NUM) == 0)
			{
				setTransportNodeCountLocalPopulationStatic(atoi(attr_value)); // TODO move
				__lclpop_arr_num = atoi(attr_value);
				__lclpop_arr = (LocalPopulation*) calloc(__lclpop_arr_num, sizeof(LocalPopulation));
				setGovernmentControlStatic(atoi(attr_value)); // TODO update
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_GOV_NUM) == 0)
			{
				setGovernmentCountStatic(atoi(attr_value));
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_LOG_MAN_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_AS_LOG_MAN_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_AS_LOG_MAN_ID);
					current_index = 0;
				}
				int id = extractObjectId(attr_value);
				addNewStructIdPtr(LOGISTICS_MANAGER_SAVE, id, &((AppState*)current_obj_ptr->data)->logistics_managers[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_CO_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_AS_CO_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_AS_CO_ID);
					current_index = 0;
				}

				addNewStructIdPtr(COMPANY_SAVE, extractObjectId(attr_value), &((AppState*)current_obj_ptr->data)->companies[current_index]);
				assignNewCompanyValues(&((AppState*)current_obj_ptr->data)->companies[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_LOC_POP_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_AS_LOC_POP_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_AS_LOC_POP_ID);
					current_index = 0;
				}

				addNewStructIdPtr(LOCAL_POPULATION_SAVE, extractObjectId(attr_value), &__lclpop_arr[current_index]);
				updateLocalPopStructPtrsFromArr(__lclpop_arr);
				current_index++;
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_GOV_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_AS_GOV_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_AS_GOV_ID);
					current_index = 0;
				}

				addNewStructIdPtr(GOVERNMENT_SAVE, extractObjectId(attr_value), getGovernmentByIndex(current_index));

				current_index++;
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_MAR_BUY_AVG_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_AS_MAR_BUY_AVG_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_AS_MAR_BUY_AVG_ID);
					current_index = 0;
				}
				int id = extractObjectId(attr_value);
				addNewStructIdPtr(
					HISTORY_WTD_AVG_ARRAY_SAVE, 
					id, 
					getMarketBuyHistoryWtdAvgArrByProduct(current_index)
				);

				current_index++;
			}
			else if (strcmp(new_data_point, SAVE_FILE_AS_MAR_SELL_AVG_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_AS_MAR_SELL_AVG_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_AS_MAR_SELL_AVG_ID);
					current_index = 0;
				}
				int id = extractObjectId(attr_value);
				addNewStructIdPtr(
					HISTORY_WTD_AVG_ARRAY_SAVE, 
					id, 
					getMarketSellHistoryWtdAvgArrByProduct(current_index)
				);

				current_index++;
			}
			break;
		case COMPANY_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_CO_CON_FAC_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_CO_CON_FAC_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_CO_CON_FAC_ID);
					current_index = 0;
				}
				
				const Factory* new_fact = loadAddNewFactoryToCompany((Company*)current_obj_ptr->data);
				addNewStructIdPtr(FACTORY_SAVE, extractObjectId(attr_value), new_fact);

				current_index++;
			}
			break;
		case FACTORY_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_FAC_PRO_REC_ID) == 0)
			{
				loadFactoryConstructor(((Factory*)current_obj_ptr->data), atoi(attr_value));
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_STO_IN_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_FAC_STO_IN_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_FAC_STO_IN_ID);
					current_index = 0;
				}
				else
				{
					current_index++;
				}

				addNewStructIdPtr(STOCKPILE_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->stockpiles_in[current_index]);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_STO_OUT_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_FAC_STO_OUT_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_FAC_STO_OUT_ID);
					current_index = 0;
				}
				else
				{
					current_index++;
				}

				addNewStructIdPtr(STOCKPILE_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->stockpiles_out[current_index]);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_STO_IN_MAX_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->stockpiles_in_max_quant[current_index] = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_STO_OUT_MAX_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->stockpiles_out_max_quant[current_index] = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_ORD_IN_ID) == 0)
			{
				addNewStructIdPtr(ORDER_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->orders_in[current_index]);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_ORD_OUT_ID) == 0)
			{
				addNewStructIdPtr(ORDER_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->orders_out[current_index]);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_ORD_NUM_IN_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->ordered_in[current_index] = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_ORD_NUM_OUT_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->ordered_out[current_index] = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_PFT_HIS_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_FAC_PFT_HIS_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_FAC_PFT_HIS_ID);
					current_index = 0;
				}

				addNewStructIdPtr(HISTORY_ARRAY_AVG_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->profit_history);

				current_index++;
			}
			break;
		case GOVERNMENT_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_GOV_CTL_LOC_ID) == 0)
			{
				setGovernmentControlByLocation(((Government*)current_obj_ptr->data), atoi(attr_value));
			}
			break;
		case HISTORY_ARRAY_SAVE:
			break;
		case HISTORY_ARRAY_AVG_SAVE:
			break;
		case HISTORY_WTD_AVG_ARRAY_SAVE:
			break;
		case LOCAL_POPULATION_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_LOC_POP_POP_CEN_ID) == 0)
			{
				addNewStructIdPtr(FACTORY_SAVE, extractObjectId(attr_value), &((LocalPopulation*)current_obj_ptr->data)->population_centre);
			}
			break;
		case LOGISTICS_CONTRACT_SAVE:
			break;
		case LOGISTICS_MANAGER_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_LOG_MAN_VEH_NUM) == 0)
			{
				loadLogisticsManagerConstructorVehicles(((LogisticsManager*)current_obj_ptr->data), atoi(attr_value));
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_MAN_CON_NUM) == 0)
			{
				loadLogisticsManagerConstructorLogisticsContract(((LogisticsManager*)current_obj_ptr->data), atoi(attr_value));
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_MAN_VEH_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_LOG_MAN_VEH_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_LOG_MAN_VEH_ID);
					current_index = 0;
				}

				addNewStructIdPtr(VEHICLE_SAVE, extractObjectId(attr_value), &(((LogisticsManager*)current_obj_ptr->data)->vehicles[current_index]));

				current_index++;
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_MAN_CON_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_LOG_MAN_CON_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_LOG_MAN_CON_ID);
					current_index = 0;
				}

				addNewStructIdPtr(LOGISTICS_CONTRACT_SAVE, extractObjectId(attr_value), &((LogisticsManager*)current_obj_ptr->data)->contracts[current_index]);

				current_index++;
			}
			break;
		case PRODUCT_MARKET_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_PRO_MAR_LOC_ID) == 0)
			{
				current_location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_PRO_MAR_PRO_ID) == 0)
			{
				current_product = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_PRO_MAR_SELL_HIS_ID) == 0)
			{
				addNewStructIdPtr(HISTORY_WTD_AVG_ARRAY_SAVE, extractObjectId(attr_value), 
					&getProductMarketAtLocation(current_location, current_product)->sell_hist_array
				);
			}
			else if (strcmp(new_data_point, SAVE_FILE_PRO_MAR_BUY_HIS_ID) == 0)
			{
				addNewStructIdPtr(HISTORY_WTD_AVG_ARRAY_SAVE, extractObjectId(attr_value), 
					&getProductMarketAtLocation(current_location, current_product)->buy_hist_array
				);
			}
			break;
		case ORDER_SAVE:
			break;
		case STOCKPILE_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_STO_QUA_HIS_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_STO_QUA_HIS_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_STO_QUA_HIS_ID);
				}

				addNewStructIdPtr(HISTORY_ARRAY_SAVE, extractObjectId(attr_value), &((Stockpile*)current_obj_ptr->data)->quantity_history);
			}
			break;
		case VEHICLE_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_VEH_STO_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_VEH_STO_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_VEH_STO_ID);
				}

				addNewStructIdPtr(STOCKPILE_SAVE, extractObjectId(attr_value), &((Vehicle*)current_obj_ptr->data)->stockpile);
			}
			break;
		default:
			break;
	}
}

static inline void setDefaults(const enum AttributeTypes current_obj_type, struct LoadStateIdList* current_obj)
{
	switch (current_obj_type)
	{
		case APP_STATE_SAVE:
			break;
		case COMPANY_SAVE:
			break;
		case FACTORY_SAVE:
			((Factory*)current_obj->data)->location = 0;
			((Factory*)current_obj->data)->processing_speed = 1;
			break;
		case GOVERNMENT_SAVE:
			((Government*)current_obj->data)->wealth = 0;
			break;
		case LOCAL_POPULATION_SAVE:
			((LocalPopulation*)current_obj->data)->population_number = 0;
			break;
		case LOGISTICS_CONTRACT_SAVE:
			((LogisticsContract*)current_obj->data)->assigned_vehicle = NULL;
			((LogisticsContract*)current_obj->data)->selling_factory = NULL;
			((LogisticsContract*)current_obj->data)->buying_factory = NULL;
			((LogisticsContract*)current_obj->data)->current_phase = 0;
			((LogisticsContract*)current_obj->data)->product = 0;
			((LogisticsContract*)current_obj->data)->quantity = 0;
			break;
		case LOGISTICS_MANAGER_SAVE:
			break;
		case ORDER_SAVE:
			((Order*)current_obj->data)->offering_factory = NULL;
			((Order*)current_obj->data)->offer_num = 0;
			((Order*)current_obj->data)->price = 0;
			break;
		case STOCKPILE_SAVE:
			((Stockpile*)current_obj->data)->product_type = 0;
			((Stockpile*)current_obj->data)->quantity = 0;
			break;
		case VEHICLE_SAVE:
			((Vehicle*)current_obj->data)->current_location = 0;
			((Vehicle*)current_obj->data)->end_location = -1;
			((Vehicle*)current_obj->data)->distance_travelled = 0;
			((Vehicle*)current_obj->data)->end_factory = NULL;
			((Vehicle*)current_obj->data)->max_capacity = 0;
			break;
		default:
			break;
	}
}

static inline void nextStructForAssignment(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList** current_obj)
{
	getNextObject(new_data_point, current_obj_type, current_obj);

	if (*current_obj == NULL) return;

	setDefaults(*current_obj_type, *current_obj);
}

static inline void assignAttributesForValues(char new_data_point[BUF_SIZE + 1], const enum AttributeTypes current_obj_type, struct LoadStateIdList* current_obj_ptr)
{
	char attr_value[BUF_SIZE];
	new_data_point++; // Removes SAVE_FILE_ATTR_ID char
	extractAttribute(new_data_point, attr_value);

	switch (current_obj_type)
	{
		case APP_STATE_SAVE:
			break;
		case COMPANY_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_CO_WTH_ID) == 0)
			{
				((Company*)current_obj_ptr->data)->wealth = atoi(attr_value);
			}
			break;
		case FACTORY_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_FAC_LOC_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_MAN_TYP_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->managementType = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_MAN_ID) == 0)
			{
				const int id = extractObjectId(attr_value);
				const enum AttributeTypes type = matchIdentifierWithType(attr_value);
				((Factory*)current_obj_ptr->data)->management = getObject(type, id)->data;
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_PRO_SPE_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->processing_speed = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_LEF_PRO_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->leftover_production = atof(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_EMP_WAG_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->employee_wages = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_CUR_EMP_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->current_employee_num = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_FAC_MAX_EMP_ID) == 0)
			{
				((Factory*)current_obj_ptr->data)->max_employee_num = atoi(attr_value);
			}
			break;
		case GOVERNMENT_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_GOV_WTH_ID) == 0)
			{
				((Government*)current_obj_ptr->data)->wealth = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_GOV_GST_ID) == 0)
			{
				((Government*)current_obj_ptr->data)->gst_rate = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_GOV_IMP_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_GOV_IMP_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_GOV_IMP_ID);
					current_index = 0;
				}
				else
				{
					current_index++;
				}

				((Government*)current_obj_ptr->data)->import_tariffs[current_index] = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_GOV_EXP_ID) == 0)
			{
				if (strcmp(current_arr_name, SAVE_FILE_GOV_EXP_ID))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s", SAVE_FILE_GOV_EXP_ID);
					current_index = 0;
				}
				else
				{
					current_index++;
				}

				((Government*)current_obj_ptr->data)->export_tariffs[current_index] = atoi(attr_value);
			}
			break;
		case HISTORY_ARRAY_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_HIS_ARR_ITEM_ID) == 0)
			{
				setValueAtIndexHistoryArray(((HistoryArray*)current_obj_ptr->data), current_index++, atoi(attr_value));
			}
			break;
		case HISTORY_ARRAY_AVG_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_HIS_ARR_AVG_ITEM_ID) == 0)
			{
				setValueAtIndexHistoryArrayAvg(((HistoryArrayAvg*)current_obj_ptr->data), current_index++, atoi(attr_value));
			}
			break;
		case HISTORY_WTD_AVG_ARRAY_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_HIS_WTD_AVG_ARR_VALUE_ID) == 0)
			{
				setValueAtIndexHistoryWtdAvgArray(((HistoryWtdAvgArray*)current_obj_ptr->data), current_index++, atoi(attr_value));
			}
			else if (strcmp(new_data_point, SAVE_FILE_HIS_WTD_AVG_ARR_WEIGHT_ID) == 0)
			{
				setWeightAtIndexHistoryWtdAvgArray(((HistoryWtdAvgArray*)current_obj_ptr->data), current_index, atoi(attr_value));
			}
			else if (strcmp(new_data_point, SAVE_FILE_HIS_WTD_AVG_ARR_AVG_ID) == 0)
			{
				setAverageAtIndexHistoryWtdAvgArray(((HistoryWtdAvgArray*)current_obj_ptr->data), current_index, atoi(attr_value));
			}
			break;
		case LOCAL_POPULATION_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_LOC_POP_POP_NUM_ID) == 0)
			{
				((LocalPopulation*)current_obj_ptr->data)->population_number = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOC_POP_WTH_ID) == 0)
			{
				((LocalPopulation*)current_obj_ptr->data)->wealth = atoi(attr_value);
			}
			break;
		case LOGISTICS_CONTRACT_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_LOG_CON_VEH_ID) == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->assigned_vehicle = (Vehicle*) getObject(VEHICLE_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_CON_SEL_FAC_ID) == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->selling_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_CON_BUY_FAC_ID) == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->buying_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_CON_CUR_PHA_ID) == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->current_phase = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_CON_PRO_ID) == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->product = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_CON_QUA_ID) == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->quantity = atoi(attr_value);
			}
			break;
		case LOGISTICS_MANAGER_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_LOG_MAN_WTH_ID) == 0)
			{
				((LogisticsManager*)current_obj_ptr->data)->wealth = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_LOG_MAN_HQ_LOC_ID) == 0)
			{
				((LogisticsManager*)current_obj_ptr->data)->headquarters_location = atoi(attr_value);
			}
			break;
		case ORDER_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_ORD_OFF_FAC_ID) == 0)
			{
				((Order*)current_obj_ptr->data)->offering_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, SAVE_FILE_ORD_OFF_NUM_ID) == 0)
			{
				((Order*)current_obj_ptr->data)->offer_num = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_ORD_PRI_ID) == 0)
			{
				((Order*)current_obj_ptr->data)->price = atoi(attr_value);
			}
			break;
		case PRODUCT_MARKET_SAVE:
			// Should never happen (can't)
			break;
		case STOCKPILE_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_STO_PRO_ID) == 0)
			{
				((Stockpile*)current_obj_ptr->data)->product_type = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_STO_QUA_ID) == 0)
			{
				((Stockpile*)current_obj_ptr->data)->quantity = atoi(attr_value);
			}
			break;
		case VEHICLE_SAVE:
			if (strcmp(new_data_point, SAVE_FILE_VEH_CUR_LOC_ID) == 0)
			{
				((Vehicle*)current_obj_ptr->data)->current_location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_VEH_END_LOC_ID) == 0)
			{
				((Vehicle*)current_obj_ptr->data)->end_location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_VEH_DIS_TRA_ID) == 0)
			{
				((Vehicle*)current_obj_ptr->data)->distance_travelled = atoi(attr_value);
			}
			else if (strcmp(new_data_point, SAVE_FILE_VEH_END_FAC_ID) == 0)
			{
				((Vehicle*)current_obj_ptr->data)->end_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, SAVE_FILE_VEH_MAX_CAP_ID) == 0)
			{
				((Vehicle*)current_obj_ptr->data)->max_capacity = atoi(attr_value);
			}
			break;
		default:
			break;
	}
}

static inline void processDataPointForPtrs(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList** current_obj)
{
	if (new_data_point[0] == SAVE_FILE_ATTR_ID)
	{
		// Add new attribute
		addNewAttributeForPtrs(new_data_point, *current_obj_type, *current_obj);
	}
	else if (new_data_point[0] == '\0')
	{
		// Blank line; ignore
	}
	else 
	{
		// Add new struct
		addNewStructForPtrs(new_data_point, current_obj_type, current_obj);
	}
}

static inline void processDataPointForValueAssignment(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList** current_obj)
{
	if (new_data_point[0] == SAVE_FILE_ATTR_ID)
	{
		// Add new attribute
		assignAttributesForValues(new_data_point, *current_obj_type, *current_obj);
	}
	else if (new_data_point[0] == '\0')
	{
		// Blank line; ignore
	}
	else 
	{
		// Add new struct
		nextStructForAssignment(new_data_point, current_obj_type, current_obj);
	}
}

static inline void assignAllNeededIds()
{
	struct LoadStateIdList* current_obj_ptr;
	int id;

	for (int i = 0; i < STRUCT_SAVE_NUM; i++)
	{
		current_obj_ptr = &__object_arr[i];
		if (current_obj_ptr->data == NULL) continue; // NOTHING LOADED OF THIS CATEGORY
		id = 0;
		switch (i)
		{
			case APP_STATE_SAVE:
				break;
			case COMPANY_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdCompany(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case FACTORY_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdFactory(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case GOVERNMENT_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdGovernment(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case HISTORY_ARRAY_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdHistoryArray(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case HISTORY_ARRAY_AVG_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdHistoryArrayAvg(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case HISTORY_WTD_AVG_ARRAY_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdHistoryWtdAvgArray(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case LOCAL_POPULATION_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdLocalPopulation(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case LOGISTICS_CONTRACT_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdLogisticsContract(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case LOGISTICS_MANAGER_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdLogisticsManager(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case ORDER_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdOrder(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case PRODUCT_MARKET_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdProductMarket(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case STOCKPILE_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdStockpile(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			case VEHICLE_SAVE:
				while (current_obj_ptr != NULL)
				{
					assignLoadIdVehicle(current_obj_ptr->data, id++);
					current_obj_ptr = current_obj_ptr->next;
				}
				break;
			default:
				break;
		}
	}
}

static inline void cleanLoadStateIdList(struct LoadStateIdList* base_ptr)
{
	struct LoadStateIdList* prev_ptr;
	while (base_ptr)
	{
		prev_ptr = base_ptr;
		base_ptr = base_ptr->next;
		free(prev_ptr);
	}
}

static inline void cleanAllLoadStateIdLists()
{
	struct LoadStateIdList* ptr;
	for (int i = 0; i < STRUCT_SAVE_NUM; i++)
	{
		ptr = &__object_arr[i];
		if (ptr->next == NULL) continue;
		cleanLoadStateIdList(ptr->next);
	}
	free(__object_arr);
}

AppState* loadAppState(const char* app_dir_path, const char* save_file_name)
{
	char save_file_path[BUF_SIZE];
	snprintf(save_file_path, BUF_SIZE, "%s\\saves\\%s", app_dir_path, save_file_name);

	char new_data_point[BUF_SIZE + 1];
	enum AttributeTypes current_obj_type;
	struct LoadStateIdList* current_obj_ptr = NULL;

	__object_arr = calloc(STRUCT_SAVE_NUM, sizeof(struct LoadStateIdList));

	// File Writing
	FILE *fptr;
	fptr = fopen(save_file_path, "r");

	if (!fptr)
	{
		printf("\nLoad file did not open\n");
		return NULL;
	}
	
	// Create and index structs and arrays
	while (getNextDataPoint(fptr, new_data_point))
	{
		processDataPointForPtrs(new_data_point, &current_obj_type, &current_obj_ptr);
		if (current_obj_ptr == NULL)
		{
			printf("\n\nError during loading: NULL obect during creation and index phase\n");
			return NULL;
		}
	}
	rewind(fptr);

	// Assign values and single ptrs
	while (getNextDataPoint(fptr, new_data_point))
	{
		processDataPointForValueAssignment(new_data_point, &current_obj_type, &current_obj_ptr);
		if (current_obj_ptr == NULL)
		{
			printf("\n\nError during loading: NULL obect during value assignment phase\n");
			return NULL;
		}
	}
	fclose(fptr);

	assignAllNeededIds();

	// Set LocalPops to static arr
	if (__lclpop_arr)
	{
		for (int i = 0; i < __lclpop_arr_num; i++)
		{
			moveLocalPopulationToStaticArray(
				&__lclpop_arr[i],
				__lclpop_arr[i].population_centre.location
			);

			// Shift other external data
			const Factory* new_loc = &getLocalPopulationByLocation(i)->population_centre;
			// Vehicles
			struct LoadStateIdList* current_obj_ptr = &__object_arr[VEHICLE_SAVE];
			if (current_obj_ptr->data != NULL)
			{
				while (current_obj_ptr != NULL)
				{
					if (((Vehicle*)current_obj_ptr->data)->end_factory == &__lclpop_arr[i].population_centre)
					{
						((Vehicle*)current_obj_ptr->data)->end_factory = new_loc;
					}
					current_obj_ptr = current_obj_ptr->next;
				}
			}
			// LogisticsContracts
			current_obj_ptr = &__object_arr[LOGISTICS_CONTRACT_SAVE];
			if (current_obj_ptr->data != NULL)
			{
				while (current_obj_ptr != NULL)
				{
					if (((LogisticsContract*)current_obj_ptr->data)->buying_factory == &__lclpop_arr[i].population_centre)
					{
						((LogisticsContract*)current_obj_ptr->data)->buying_factory = new_loc;
					}
					if (((LogisticsContract*)current_obj_ptr->data)->selling_factory == &__lclpop_arr[i].population_centre)
					{
						((LogisticsContract*)current_obj_ptr->data)->selling_factory = new_loc;
					}
					current_obj_ptr = current_obj_ptr->next;
				}
			}
		}

		free(__lclpop_arr);
		__lclpop_arr = NULL;
		__lclpop_arr_num = 0;
	}

	AppState* result = (AppState*) __object_arr[APP_STATE_SAVE].data;// First element (Should be only)

	// Assign orders to PMs
	for (int i = 0; i < result->companies_num; i++)
	{
		loadCompanyAssignOrders(&result->companies[i]);
	}
	for (int i = 0; i < getLocalPopulationNum(); i++)
	{
		loadLocalPopulationAssignOrders(getLocalPopulationByLocation(i));
	}

	cleanAllLoadStateIdLists();

	return result; // First element (Should be only)
}

