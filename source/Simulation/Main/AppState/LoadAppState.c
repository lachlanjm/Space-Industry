#include "LoadAppState.h"

// LOADING OBJECT REPOSITORY
static struct LoadStateIdList* __app_state_arr = NULL;
static struct LoadStateIdList* __factory_manager_arr = NULL;
static struct LoadStateIdList* __factory_arr = NULL;
static struct LoadStateIdList* __logistics_contract_arr = NULL;
static struct LoadStateIdList* __logistics_manager_arr = NULL;
static struct LoadStateIdList* __order_arr = NULL;
static struct LoadStateIdList* __stockpile_arr = NULL;
static struct LoadStateIdList* __vehicle_arr = NULL;

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

static inline enum AttributeTypes matchIdentifierWithType(char* id)
{
	if (strcmp(id, SAVE_FILE_APP_STATE_ID) == 0)
	{
		return APP_STATE_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_FACTORY_MANAGER_ID) == 0)
	{
		return FACTORY_MANAGER_SAVE;
	}
	else if (strcmp(id, SAVE_FILE_FACTORY_ID) == 0)
	{
		return FACTORY_SAVE;
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
	int result = atoi(&ptr_string_id[i]);
	if (result == 0 && ptr_string_id[i] != '0')
	{
		return -1;
	}
	return result;
}

static inline void extractAttribute(char* new_data_point, char* attribute_value_buffer)
{
	int i = 0;
	while (new_data_point[i] != SAVE_FILE_ID_SEP)
	{
		if (new_data_point[i] == '\0')
		{
			return
		}
		i++;
	}
	new_data_point[i++] = '\0'; // Removes the unnecessary data after
	snprintf(attribute_value_buffer, BUF_SIZE, "%s", &new_data_point[i]);
}

static inline void addNewStructIdPtr(const enum AttributeTypes obj_type, const int id, const void* data)
{
	struct LoadStateIdList* base_item;
	switch (obj_type)
	{
		case APP_STATE_SAVE:
			if (__app_state_arr)
			{
				base_item = __app_state_arr;
				break;
			}
			__app_state_arr = calloc(1, sizeof(struct LoadStateIdList));
			__app_state_arr->data = data;
			__app_state_arr->id = id;
			__app_state_arr->next = NULL;
			return;
		case FACTORY_MANAGER_SAVE:
			if (__factory_manager_arr)
			{
				base_item = __factory_manager_arr;
				break;
			}
			__factory_manager_arr = calloc(1, sizeof(struct LoadStateIdList));
			__factory_manager_arr->data = data;
			__factory_manager_arr->id = id;
			__factory_manager_arr->next = NULL;
			return;
		case FACTORY_SAVE:
			if (__factory_arr)
			{
				base_item = __factory_arr;
				break;
			}
			__factory_arr = calloc(1, sizeof(struct LoadStateIdList));
			__factory_arr->data = data;
			__factory_arr->id = id;
			__factory_arr->next = NULL;
			return;
		case LOGISTICS_CONTRACT_SAVE:
			if (__logistics_contract_arr)
			{
				base_item = __logistics_contract_arr;
				break;
			}
			__logistics_contract_arr = calloc(1, sizeof(struct LoadStateIdList));
			__logistics_contract_arr->data = data;
			__logistics_contract_arr->id = id;
			__logistics_contract_arr->next = NULL;
			return;
		case LOGISTICS_MANAGER_SAVE:
			if (__logistics_manager_arr)
			{
				base_item = __logistics_manager_arr;
				break;
			}
			__logistics_manager_arr = calloc(1, sizeof(struct LoadStateIdList));
			__logistics_manager_arr->data = data;
			__logistics_manager_arr->id = id;
			__logistics_manager_arr->next = NULL;
			return;
		case ORDER_SAVE:
			if (__order_arr)
			{
				base_item = __order_arr;
				break;
			}
			__order_arr = calloc(1, sizeof(struct LoadStateIdList));
			__order_arr->data = data;
			__order_arr->id = id;
			__order_arr->next = NULL;
			return;
		case STOCKPILE_SAVE:
			if (__stockpile_arr)
			{
				base_item = __stockpile_arr;
				break;
			}
			__stockpile_arr = calloc(1, sizeof(struct LoadStateIdList));
			__stockpile_arr->data = data;
			__stockpile_arr->id = id;
			__stockpile_arr->next = NULL;
			return;
		case VEHICLE_SAVE:
			if (__vehicle_arr)
			{
				base_item = __vehicle_arr;
				break;
			}
			__vehicle_arr = calloc(1, sizeof(struct LoadStateIdList));
			__vehicle_arr->data = data;
			__vehicle_arr->id = id;
			__vehicle_arr->next = NULL;
			return;
		default:
			return; // Error
	}

	while (base_item->next)
	{
		base_item = base_item->next;
	}

	base_item->next = calloc(1, sizeof(struct LoadStateIdList));
	base_item->next->data = data;
	base_item->next->id = id;
	base_item->next->next = NULL;
}

static inline struct LoadStateIdList* getItemWithId(const struct LoadStateIdList* item, const int id)
{	
	while (item != NULL)
	{
		if (item->id == id)
		{
			break;
		}
		item = item->next;
	}

	return item
}

static inline struct LoadStateIdList* getObject(const enum AttributeTypes obj_type, const int id)
{
	switch (obj_type)
	{
		case APP_STATE_SAVE:
			return getItemWithId(__app_state_arr, id);
		case FACTORY_MANAGER_SAVE:
			return getItemWithId(__factory_manager_arr, id);
		case FACTORY_SAVE:
			return getItemWithId(__factory_arr, id);
		case LOGISTICS_CONTRACT_SAVE:
			return getItemWithId(__logistics_contract_arr, id);
		case LOGISTICS_MANAGER_SAVE:
			return getItemWithId(__logistics_manager_arr, id);
		case ORDER_SAVE:
			return getItemWithId(__order_arr, id);
		case STOCKPILE_SAVE:
			return getItemWithId(__stockpile_arr, id);
		case VEHICLE_SAVE:
			return getItemWithId(__vehicle_arr, id);
		default:
			return NULL;
	}
}

static inline void getNextObject(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList* current_obj_item)
{
	int id = extractObjectId(new_data_point);
	*current_obj_type = matchIdentifierWithType(new_data_point);
	current_obj_ptr = getObject(*current_obj_type, id);
}

static inline void addNewStructForPtrs(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList* current_obj_ptr)
{
	int id = extractObjectId(new_data_point);
	*current_obj_type = matchIdentifierWithType(new_data_point);
	if (*current_obj_type == APP_STATE_SAVE && id >= __app_state_arr_num)
	{
		realloc(__app_state_arr, (id+1) * sizeof(AppState*));
		__app_state_arr[id] = (AppState*) calloc(sizeof(AppState));
	}
	current_obj_ptr = getObject(*current_obj_type, id);
}

static int current_index = 0;
static char current_arr_name[BUF_SIZE] = "";
static inline void addNewAttributeForPtrs(char new_data_point[BUF_SIZE + 1], const enum AttributeTypes current_obj_type, struct LoadStateIdList* current_obj_ptr)
{
	char attr_value[BUF_SIZE];
	new_data_point++; // Removes SAVE_FILE_ATTR_ID char
	extractAttribute(new_data_point, attr_value);

	switch (obj_type)
	{
		case APP_STATE_SAVE:
			if (strcmp(new_data_point, "logistics_managers_num") == 0)
			{
				int num = atoi(attr_value);
				((AppState*)current_obj_ptr->data)->logistics_managers_num = num;
				((AppState*)current_obj_ptr->data)->logistics_managers_next_process_tick_index = 0;
				((AppState*)current_obj_ptr->data)->logistics_managers = (LogisticsManager*) calloc(((AppState*)current_obj_ptr->data)->logistics_managers_num, sizeof(LogisticsManager));
			}
			else if (strcmp(new_data_point, "factory_managers_num") == 0)
			{
				((AppState*)current_obj_ptr->data)->factory_managers_num = atoi(attr_value);
				((AppState*)current_obj_ptr->data)->factory_managers = (FactoryManager*) calloc(((AppState*)current_obj_ptr->data)->factory_managers_num, sizeof(FactoryManager));
			}
			else if (strcmp(new_data_point, "logistics_managers") == 0)
			{
				if (strcmp(current_arr_name, "logistics_managers"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "logistics_managers");
					current_index = 0;
				}

				addNewStructIdPtr(LOGISTICS_MANAGER_SAVE, extractObjectId(attr_value), &((AppState*)current_obj_ptr->data)->logistics_managers[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, "factory_managers") == 0)
			{
				if (strcmp(current_arr_name, "factory_managers"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "factory_managers");
					current_index = 0;
				}

				addNewStructIdPtr(FACTORY_MANAGER_SAVE, extractObjectId(attr_value), &((AppState*)current_obj_ptr->data)->factory_managers[current_index]);

				current_index++;
			}
			break;
		case FACTORY_MANAGER_SAVE:
			if (strcmp(new_data_point, "controlled_factory") == 0)
			{
				if (strcmp(current_arr_name, "controlled_factory"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "controlled_factory");
					current_index = 0;
				}

				addNewStructIdPtr(FACTORY_SAVE, extractObjectId(attr_value), &((FactoryManager*)current_obj_ptr->data)->controlled_factory);

				current_index++;
			}
			break;
		case FACTORY_SAVE:
			if (strcmp(new_data_point, "production_recipe") == 0)
			{
				loadFactoryConstructor(((Factory*)current_obj_ptr->data), atoi(attr_value));
			}
			else if (strcmp(new_data_point, "stockpiles_in") == 0)
			{
				if (strcmp(current_arr_name, "stockpiles_in"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "stockpiles_in");
					current_index = 0;
				}

				addNewStructIdPtr(STOCKPILE_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->stockpiles_in[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, "stockpiles_out") == 0)
			{
				if (strcmp(current_arr_name, "stockpiles_out"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "stockpiles_out");
					current_index = 0;
				}

				addNewStructIdPtr(STOCKPILE_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->stockpiles_out[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, "orders_in") == 0)
			{
				if (strcmp(current_arr_name, "orders_in"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "orders_in");
					current_index = 0;
				}

				addNewStructIdPtr(ORDER_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->orders_in[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, "orders_out") == 0)
			{
				if (strcmp(current_arr_name, "orders_out"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "orders_out");
					current_index = 0;
				}

				addNewStructIdPtr(ORDER_SAVE, extractObjectId(attr_value), &((Factory*)current_obj_ptr->data)->orders_out[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, "ordered_in") == 0)
			{
				if (strcmp(current_arr_name, "ordered_in"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "ordered_in");
					current_index = 0;
				}

				((Factory*)current_obj_ptr->data)->ordered_in[current_index] = atoi(attr_value);

				current_index++;
			}
			else if (strcmp(new_data_point, "ordered_out") == 0)
			{
				if (strcmp(current_arr_name, "ordered_out"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "ordered_out");
					current_index = 0;
				}

				((Factory*)current_obj_ptr->data)->ordered_out[current_index] = atoi(attr_value);

				current_index++;
			}
			break;
		case LOGISTICS_CONTRACT_SAVE:
			break;
		case LOGISTICS_MANAGER_SAVE:
			if (strcmp(new_data_point, "vehicles_num") == 0)
			{
				loadLogisticsManagerConstructorVehicles(((LogisticsManager*)current_obj_ptr->data), atoi(attr_value));
			}
			else if (strcmp(new_data_point, "contracts_num") == 0)
			{
				loadLogisticsManagerConstructorLogisticsContract(((LogisticsManager*)current_obj_ptr->data), atoi(attr_value));
			}
			else if (strcmp(new_data_point, "vehicles") == 0)
			{
				if (strcmp(current_arr_name, "vehicles"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "vehicles");
					current_index = 0;
				}

				addNewStructIdPtr(VEHICLE_SAVE, extractObjectId(attr_value), &((LogisticsManager*)current_obj_ptr->data)->vehicles[current_index]);

				current_index++;
			}
			else if (strcmp(new_data_point, "contracts") == 0)
			{
				if (strcmp(current_arr_name, "contracts"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "contracts");
					current_index = 0;
				}

				addNewStructIdPtr(LOGISTICS_CONTRACT_SAVE, extractObjectId(attr_value), &((LogisticsManager*)current_obj_ptr->data)->contracts[current_index]);

				current_index++;
			}
			break;
		case ORDER_SAVE:
			break;
		case STOCKPILE_SAVE:
			break;
		case VEHICLE_SAVE:
			if (strcmp(new_data_point, "stockpile") == 0)
			{
				if (strcmp(current_arr_name, "stockpile"))
				{
					snprintf(current_arr_name, BUF_SIZE, "%s" "stockpile");
					current_index = 0;
				}

				addNewStructIdPtr(STOCKPILE_SAVE, extractObjectId(attr_value), &((Vehicle*)current_obj_ptr->data)->stockpile);

				current_index++;
			}
			break;
		default:
			break;
	}
}

static inline void nextStructForAssignment(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList* current_obj)
{
	getNextObject(new_data_point, current_obj_type, current_obj);

	// SET DEFAULTS
	switch (*current_obj_type)
	{
		case APP_STATE_SAVE:
			break;
		case FACTORY_MANAGER_SAVE:
			break;
		case FACTORY_SAVE:
			((Factory*)current_obj_ptr->data)->location = 0;
			((Factory*)current_obj_ptr->data)->processing_speed = 0;
			break;
		case LOGISTICS_CONTRACT_SAVE:
			((LogisticsContract*)current_obj_ptr->data)->assigned_vehicle = NULL;
			((LogisticsContract*)current_obj_ptr->data)->selling_factory = NULL;
			((LogisticsContract*)current_obj_ptr->data)->buying_factory = NULL;
			((LogisticsContract*)current_obj_ptr->data)->current_phase = 0;
			((LogisticsContract*)current_obj_ptr->data)->product = 0;
			((LogisticsContract*)current_obj_ptr->data)->quantity = 0;
			break;
		case LOGISTICS_MANAGER_SAVE:
			break;
		case ORDER_SAVE:
			((Order*)current_obj_ptr->data)->offering_factory = NULL;
			((Order*)current_obj_ptr->data)->offer_num = 0;
			((Order*)current_obj_ptr->data)->price = 0;
			break;
		case STOCKPILE_SAVE:
			((Stockpile*)current_obj_ptr->data)->product_type = 0;
			((Stockpile*)current_obj_ptr->data)->quantity = 0;
			break;
		case VEHICLE_SAVE:
			((Vehicle*)current_obj_ptr->data)->current_location = 0;
			((Vehicle*)current_obj_ptr->data)->end_location = 0;
			((Vehicle*)current_obj_ptr->data)->distance_travelled = 0;
			((Vehicle*)current_obj_ptr->data)->end_factory = NULL;
			((Vehicle*)current_obj_ptr->data)->max_capacity = 0;
			break;
		default:
			return NULL;
	}
}

static inline void assignNewAttributesForValues(char new_data_point[BUF_SIZE + 1], const enum AttributeTypes current_obj_type, struct LoadStateIdList* current_obj_ptr)
{
	char attr_value[BUF_SIZE];
	new_data_point++; // Removes SAVE_FILE_ATTR_ID char
	extractAttribute(new_data_point, attr_value);

	switch (obj_type)
	{
		case APP_STATE_SAVE:
			break;
		case FACTORY_MANAGER_SAVE:
			break;
		case FACTORY_SAVE:
			if (strcmp(new_data_point, "location") == 0)
			{
				((Factory*)current_obj_ptr->data)->location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "processing_speed") == 0)
			{
				((Factory*)current_obj_ptr->data)->processing_speed = atoi(attr_value);
			}
			break;
		case LOGISTICS_CONTRACT_SAVE:
			if (strcmp(new_data_point, "assigned_vehicle") == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->assigned_vehicle = (Vehicle*) getObject(VEHICLE_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, "selling_factory") == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->selling_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, "buying_factory") == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->buying_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, "current_phase") == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->current_phase = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "product") == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->product = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "quantity") == 0)
			{
				((LogisticsContract*)current_obj_ptr->data)->quantity = atoi(attr_value);
			}
			break;
		case LOGISTICS_MANAGER_SAVE:
			break;
		case ORDER_SAVE:
			if (strcmp(new_data_point, "offering_factory") == 0)
			{
				((Order*)current_obj_ptr->data)->offering_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, "offer_num") == 0)
			{
				((Order*)current_obj_ptr->data)->offer_num = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "price") == 0)
			{
				((Order*)current_obj_ptr->data)->price = atoi(attr_value);
			}
			break;
		case STOCKPILE_SAVE:
			if (strcmp(new_data_point, "product_type") == 0)
			{
				((Stockpile*)current_obj_ptr->data)->product_type = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "quantity") == 0)
			{
				((Stockpile*)current_obj_ptr->data)->quantity = atoi(attr_value);
			}
			break;
		case VEHICLE_SAVE:
			if (strcmp(new_data_point, "current_location") == 0)
			{
				((Vehicle*)current_obj_ptr->data)->current_location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "end_location") == 0)
			{
				((Vehicle*)current_obj_ptr->data)->end_location = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "distance_travelled") == 0)
			{
				((Vehicle*)current_obj_ptr->data)->distance_travelled = atoi(attr_value);
			}
			else if (strcmp(new_data_point, "end_factory") == 0)
			{
				((Vehicle*)current_obj_ptr->data)->end_factory = (Factory*) getObject(FACTORY_SAVE, extractObjectId(attr_value))->data;
			}
			else if (strcmp(new_data_point, "max_capacity") == 0)
			{
				((Vehicle*)current_obj_ptr->data)->max_capacity = atoi(attr_value);
			}
			break;
		default:
			break;
	}
}

static inline void processDataPointForPtrs(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList* current_obj)
{
	if (new_data_point[0] == SAVE_FILE_ATTR_ID)
	{
		// Add new attribute
		addNewAttributeForPtrs(new_data_point, *current_obj_type, current_obj);
	}
	else if (new_data_point[0] == SAVE_FILE_NEXT_ATTR_SEP)
	{
		// Blank line; ignore
	}
	else 
	{
		// Add new struct
		addNewStructForPtrs(new_data_point, current_obj_type, current_obj);
	}
}

static inline void processDataPointForValueAssignment(char new_data_point[BUF_SIZE + 1], enum AttributeTypes* current_obj_type, struct LoadStateIdList* current_obj)
{
	if (new_data_point[0] == SAVE_FILE_ATTR_ID)
	{
		// Add new attribute
		assignNewAttributesForValues(new_data_point, *current_obj_type, current_obj);
	}
	else if (new_data_point[0] == SAVE_FILE_NEXT_ATTR_SEP)
	{
		// Blank line; ignore
	}
	else 
	{
		// Add new struct
		nextStructForAssignment(new_data_point, current_obj_type, current_obj);
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

AppState* loadAppState(const char* app_dir_path, const char* save_file_name)
{
	char save_file_path[BUF_SIZE];
	snprintf(save_file_path, BUF_SIZE, "%s\\saves\\%s.txt", app_dir_path, save_file_name);

	char new_data_point[BUF_SIZE + 1];
	enum AttributeTypes current_obj_type;
	struct LoadStateIdList* current_obj_ptr = NULL;

	// File Writing
	FILE *fptr;
	fptr = fopen(save_file_path, "r");
	
	// Create and index structs
	while (getNextDataPoint(fptr, new_data_point))
	{
		processDataPointForPtrs(new_data_point, &current_obj_type, current_obj_ptr);
	}

	rewind(fptr);

	// Assign values
	while (getNextDataPoint(fptr, new_data_point))
	{
		processDataPointForValueAssignment(new_data_point, &current_obj_type, current_obj_ptr);
	}

	// Assign orders to PMs
	for (int i = 0; i < ((AppState*) __app_state_arr->data)->factory_managers_num; i++)
	{
		loadFactoryManagerAssignOrders(&((AppState*) __app_state_arr->data)->factory_managers[i]);
	}

	// ASSIGN IDS SOMEWHERE????

	cleanLoadStateIdList(__app_state_arr);
	cleanLoadStateIdList(__factory_manager_arr);
	cleanLoadStateIdList(__factory_arr);
	cleanLoadStateIdList(__logistics_contract_arr);
	cleanLoadStateIdList(__logistics_manager_arr);
	cleanLoadStateIdList(__order_arr);
	cleanLoadStateIdList(__stockpile_arr);
	cleanLoadStateIdList(__vehicle_arr);

	fclose(fptr);
	return (AppState*) __app_state_arr->data; // First element
}
/*
{
	for (int loc = 0; loc < TRANSPORT_NODE_COUNT; loc++)
	{
		for (int product = 0; product < PRODUCT_COUNT; product++)
		{
			getProductMarketAtLocation(loc, product)->highest_buy_order = NULL;
			getProductMarketAtLocation(loc, product)->lowest_sell_order = NULL;
		}
	}
}
*/