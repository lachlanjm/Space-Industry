#include "SaveAppState.h"

static struct SaveStateQueue* first_item;

static inline char* getSaveFormatName(const enum AttributeTypes attributeType, const int id)
{
	char buffer[BUF_SIZE];
	switch(attributeType)
	{
		case APP_STATE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "AppState");
			break;
		case FACTORY_MANAGER_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "FactoryManager");
			break;
		case FACTORY_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "Factory");
			break;
		case LOGISTICS_CONTRACT_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "LogisticsContract");
			break;
		case LOGISTICS_MANAGER_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "LogisticsManager");
			break;
		case ORDER_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "Order");
			break;
		case STOCKPILE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "Stockpile");
			break;
		case VEHICLE_SAVE:
			snprintf(buffer, BUF_SIZE, "%s", "Vehicle");
			break;
		default:
			snprintf(buffer, BUF_SIZE, "%s", "Default");
			break;
	}
	snprintf(buffer, BUF_SIZE, "%.*s%s%d", BUF_SIZE - 5, buffer, SAVE_FILE_ID_SEP, id);
	return buffer;
}

static inline char* getSaveFormatPtrString(const enum AttributeTypes attributeType, const int id)
{
	char buffer[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%s%.*s", SAVE_FILE_PTR_PREFIX, BUF_SIZE - 2, getSaveFormatName(attributeType, id));
	return buffer;
}

static inline char* getSaveFormatStringAttribute(const char* attribute_name, const char* str)
{
	char buffer[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%s%s%.*s", attribute_name, SAVE_FILE_SEP, BUF_SIZE - 20, str);
	return buffer;
}

static inline char* getSaveFormatIntegerAttribute(const char* attribute_name, const int integer)
{
	char buffer[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%s%s%.*d", attribute_name, SAVE_FILE_SEP, BUF_SIZE - 20, integer);
	return buffer;
}

static inline char* getSaveFormatUnsignedIntegerAttribute(const char* attribute_name, const uint u_integer)
{
	char buffer[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%s%s%.*u", attribute_name, SAVE_FILE_SEP, BUF_SIZE - 20, u_integer);
	return buffer;
}

static inline char* getSaveFormatPointerAttribute(const char* attribute_name, const enum AttributeTypes attributeType, const int id)
{
	char buffer[BUF_SIZE];
	snprintf(buffer, BUF_SIZE, "%s%s%.*s", attribute_name, SAVE_FILE_SEP, BUF_SIZE - 20, getSaveFormatPtrString(attributeType, id));
	return buffer;
}

static inline int writeToFile(FILE* fptr, const enum WriteType write_func, const char* str)
{
	switch (write_func)
	{
		case NEW_STRUCT_WRITE:
			return fprintf(fptr, "%s\n", str);
		case ADD_ATTRIBUTE_WRITE:
			return fprintf(fptr, "\t%s\n", str);
		case BLANK_LINE:
			return fprintf(fptr, "\n");
		default:
			return fprintf(fptr, "%s\n", str);
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

static inline void saveAppState(FILE* fptr, AppState* appState)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(APP_STATE_SAVE, 0));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("logistics_managers_num", appState->logistics_managers_num)
	);
	for (int i = 0; i < appState->logistics_managers_num; i++)
	{
		appendToQueue(LOGISTICS_MANAGER_SAVE, appState->logistics_managers[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute("logistics_managers", LOGISTICS_MANAGER_SAVE, appState->logistics_managers[i].id)
		);
	}
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("factory_managers_num", appState->logistics_managers_num)
	);
	for (int i = 0; i < appState->factory_managers_num; i++)
	{
		appendToQueue(FACTORY_MANAGER_SAVE, appState->factory_managers[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute("factory_managers", FACTORY_MANAGER_SAVE, appState->factory_managers[i].id)
		);
	}
}

static inline void saveFactoryManager(FILE* fptr, FactoryManager* factoryManager)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(FACTORY_MANAGER_SAVE, factoryManager->id));
	appendToQueue(FACTORY_SAVE, &factoryManager->controlled_factory);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute("controlled_factory", FACTORY_SAVE, factoryManager->controlled_factory.id)
	);
}

static inline void saveFactory(FILE* fptr, Factory* factory)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(FACTORY_SAVE, factory->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute("productionRecipe", factory->productionRecipe)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute("location", factory->location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("processing_speed", factory->processing_speed)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("stockpiles_in_num", factory->stockpiles_in_num)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("stockpiles_out_num", factory->stockpiles_out_num)
	);

	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		appendToQueue(STOCKPILE_SAVE, factory->stockpiles_in[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute("stockpiles_in", STOCKPILE_SAVE, factory->stockpiles_in[i].id)
		);
		appendToQueue(ORDER_SAVE, factory->orders_in[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute("orders_in", ORDER_SAVE, factory->orders_in[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatUnsignedIntegerAttribute("ordered_in", factory->ordered_in[i])
		);
	}

	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		appendToQueue(STOCKPILE_SAVE, factory->stockpiles_out[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute("stockpiles_out", STOCKPILE_SAVE, factory->stockpiles_out[i].id)
		);
		appendToQueue(ORDER_SAVE, factory->orders_out[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE,
			getSaveFormatPointerAttribute("orders_out", ORDER_SAVE, factory->orders_out[i].id)
		);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatUnsignedIntegerAttribute("ordered_out", factory->ordered_out[i])
		);
	}
}

static inline void saveLogisticsContract(FILE* fptr, LogisticsContract* logisticsContract)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(LOGISTICS_CONTRACT_SAVE, logisticsContract->id));
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute("assigned_vehicle", VEHICLE_SAVE, logisticsContract->assigned_vehicle->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute("selling_factory", FACTORY_SAVE, logisticsContract->selling_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute("buying_factory", FACTORY_SAVE, logisticsContract->buying_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute("current_phase", logisticsContract->current_phase)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute("product", logisticsContract->product)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("quantity", logisticsContract->quantity)
	);
}

static inline void saveLogisticsManager(FILE* fptr, LogisticsManager* logisticsManager)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(LOGISTICS_MANAGER_SAVE, logisticsManager->id));
	
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("vehicles_num", logisticsManager->vehicles_num)
	);
	for (int i = 0; i < logisticsManager->vehicles_num; i++)
	{
		appendToQueue(VEHICLE_SAVE, logisticsManager->vehicles[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute("vehicles", VEHICLE_SAVE, logisticsManager->vehicles[i].id)
		);
	}

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("contracts_num", logisticsManager->contracts_num)
	);
	for (int i = 0; i < logisticsManager->contracts_num; i++)
	{
		appendToQueue(LOGISTICS_CONTRACT_SAVE, logisticsManager->contracts[i]);
		writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
			getSaveFormatPointerAttribute("contracts", LOGISTICS_CONTRACT_SAVE logisticsManager->contracts[i].id)
		);
	}
}

static inline void saveOrder(FILE* fptr, Order* order)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(ORDER_SAVE, order->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPointerAttribute("offering_factory", FACTORY_SAVE, order->offering_factory->id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("offer_num", order->offer_num)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("price", order->price)
	);
}

static inline void saveStockpile(FILE* fptr, Stockpile* stockpile)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(STOCKPILE_SAVE, stockpile->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("product_type", stockpile->product_type)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("quantity", stockpile->quantity)
	);
}

static inline void saveVehicle(FILE* fptr, Vehicle* vehicle)
{
	writeToFile(fptr, NEW_STRUCT_WRITE, getSaveFormatName(VEHICLE_SAVE, vehicle->id));

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute("current_location", vehicle->current_location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatIntegerAttribute("end_location", vehicle->end_location)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("distance_travelled", vehicle->distance_travelled)
	);

	appendToQueue(STOCKPILE_SAVE, &vehicle->stockpile);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPtrString("stockpile", STOCKPILE_SAVE, vehicle->stockpile.id)
	);

	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatPtrString("end_factory", FACTORY_SAVE, vehicle->end_factory.id)
	);
	writeToFile(fptr, ADD_ATTRIBUTE_WRITE, 
		getSaveFormatUnsignedIntegerAttribute("max_capacity", vehicle->max_capacity)
	);
}

static inline void saveNextStruct(FILE* fptr, struct SaveStateQueue* item)
{
	switch (item->type)
	{
		case APP_STATE_SAVE:
			saveAppState(fptr, (AppState*) item->data);
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
	const char save_file_path[2*BUF_SIZE];
	snprintf(save_file_path, 2*BUF_SIZE, "%s\\saves\\%s.txt", appState->app_dir_path, save_file_name);
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
