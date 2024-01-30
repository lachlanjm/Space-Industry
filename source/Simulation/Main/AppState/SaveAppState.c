#include "SaveAppState.h"

static struct SaveStateQueue* first_item;

static inline char* getSaveFormatName(char buffer[BUF_SIZE], const enum AttributeTypes attributeType, const int id)
{
	switch(attributeType)
	{
		case APP_STATE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_APP_STATE_ID);
			break;
		case FACTORY_MANAGER_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_FACTORY_MANAGER_ID);
			break;
		case FACTORY_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", SAVE_FILE_FACTORY_ID);
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
	char* buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, APP_STATE_SAVE, 0));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "logistics_managers_num", appState->logistics_managers_num)
	);
	for (int i = 0; i < appState->logistics_managers_num; i++)
	{
		appendToQueue(LOGISTICS_MANAGER_SAVE, &appState->logistics_managers[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, "logistics_managers", LOGISTICS_MANAGER_SAVE, appState->logistics_managers[i].id)
		);
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "factory_managers_num", appState->factory_managers_num)
	);
	for (int i = 0; i < appState->factory_managers_num; i++)
	{
		appendToQueue(FACTORY_MANAGER_SAVE, &appState->factory_managers[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, "factory_managers", FACTORY_MANAGER_SAVE, appState->factory_managers[i].id)
		);
	}
}

static inline void saveFactoryManager(FILE* fptr, FactoryManager* factoryManager)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, FACTORY_MANAGER_SAVE, factoryManager->id));
	appendToQueue(FACTORY_SAVE, &factoryManager->controlled_factory);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, "controlled_factory", FACTORY_SAVE, factoryManager->controlled_factory.id)
	);
}

static inline void saveFactory(FILE* fptr, Factory* factory)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, FACTORY_SAVE, factory->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, "productionRecipe", factory->productionRecipe)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, "location", factory->location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "processing_speed", factory->processing_speed)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "stockpiles_in_num", factory->stockpiles_in_num)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "stockpiles_out_num", factory->stockpiles_out_num)
	);

	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		appendToQueue(STOCKPILE_SAVE, &factory->stockpiles_in[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, "stockpiles_in", STOCKPILE_SAVE, factory->stockpiles_in[i].id)
		);
		appendToQueue(ORDER_SAVE, &factory->orders_in[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, "orders_in", ORDER_SAVE, factory->orders_in[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatUnsignedIntegerAttribute(buffer, "ordered_in", factory->ordered_in[i])
		);
	}

	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		appendToQueue(STOCKPILE_SAVE, &factory->stockpiles_out[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, "stockpiles_out", STOCKPILE_SAVE, factory->stockpiles_out[i].id)
		);
		appendToQueue(ORDER_SAVE, &factory->orders_out[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute(buffer, "orders_out", ORDER_SAVE, factory->orders_out[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatUnsignedIntegerAttribute(buffer, "ordered_out", factory->ordered_out[i])
		);
	}
}

static inline void saveLogisticsContract(FILE* fptr, LogisticsContract* logisticsContract)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, LOGISTICS_CONTRACT_SAVE, logisticsContract->id));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, "assigned_vehicle", VEHICLE_SAVE, logisticsContract->assigned_vehicle->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, "selling_factory", FACTORY_SAVE, logisticsContract->selling_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, "buying_factory", FACTORY_SAVE, logisticsContract->buying_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, "current_phase", logisticsContract->current_phase)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, "product", logisticsContract->product)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "quantity", logisticsContract->quantity)
	);
}

static inline void saveLogisticsManager(FILE* fptr, LogisticsManager* logisticsManager)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, LOGISTICS_MANAGER_SAVE, logisticsManager->id));
	
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "vehicles_num", logisticsManager->vehicles_num)
	);
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		appendToQueue(VEHICLE_SAVE, &logisticsManager->vehicles[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, "vehicles", VEHICLE_SAVE, logisticsManager->vehicles[i].id)
		);
	}

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "contracts_num", logisticsManager->contracts_num)
	);
	for (int i = 0; i < logisticsManager->contracts_num; i++)
	{
		appendToQueue(LOGISTICS_CONTRACT_SAVE, &logisticsManager->contracts[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, "contracts", LOGISTICS_CONTRACT_SAVE, logisticsManager->contracts[i].id)
		);
	}
}

static inline void saveOrder(FILE* fptr, Order* order)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, ORDER_SAVE, order->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, "offering_factory", FACTORY_SAVE, order->offering_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "offer_num", order->offer_num)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "price", order->price)
	);
}

static inline void saveStockpile(FILE* fptr, Stockpile* stockpile)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, STOCKPILE_SAVE, stockpile->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "product_type", stockpile->product_type)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "quantity", stockpile->quantity)
	);
}

static inline void saveVehicle(FILE* fptr, Vehicle* vehicle)
{
	char buffer[BUF_SIZE];
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(buffer, VEHICLE_SAVE, vehicle->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, "current_location", vehicle->current_location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute(buffer, "end_location", vehicle->end_location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "distance_travelled", vehicle->distance_travelled)
	);

	appendToQueue(STOCKPILE_SAVE, &vehicle->stockpile);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute(buffer, "stockpile", STOCKPILE_SAVE, vehicle->stockpile.id)
	);

	if (vehicle->end_factory != NULL)
	{
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute(buffer, "end_factory", FACTORY_SAVE, vehicle->end_factory->id)
		);
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute(buffer, "max_capacity", vehicle->max_capacity)
	);
}

static inline void saveNextStruct(FILE* fptr, struct SaveStateQueue* item)
{
	switch (item->type)
	{
		case APP_STATE_SAVE:
			saveAppStateFormat(fptr, (AppState*) item->data);
			break;
		case FACTORY_MANAGER_SAVE:
			saveFactoryManager(fptr, (FactoryManager*) item->data);
			break;
		case FACTORY_SAVE:
			saveFactory(fptr, (Factory*) item->data);
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

int saveAppState(AppState* appState, const char* save_file_name)
{
	// Save app state
	char save_file_path[BUF_SIZE];
	snprintf(save_file_path, BUF_SIZE, "%s\\saves\\%s.txt", appState->app_dir_path, save_file_name);
	// TODO !!!!!!!!!!!!!!! ADD SAVE FILE COLLISION HANDLING!!!

	// Queue creation
	first_item = createQueue(appState);
	struct SaveStateQueue* current_item = first_item;

	// File Writing
	FILE *fptr;
	fptr = fopen(save_file_path, "w");
	
	while (current_item != NULL)
	{
		saveNextStruct(fptr, current_item);
		current_item = current_item->next;
	}

	fclose(fptr);
	cleanUpQueue();
	return 0;
}
