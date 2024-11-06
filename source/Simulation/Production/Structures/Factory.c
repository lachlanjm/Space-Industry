#include "Factory.h"

static FACTORY_ID_INT id_next = 0;
static int wage_tick_index = 0;

Factory* newFactory(const ProductionRecipe productionRecipe, const TransportNode location)
{
	Factory* factory = (Factory*) calloc(1, sizeof(Factory));

	assignFactoryValuesCompany(factory, NULL, productionRecipe, location); // TODO make this better

	return factory;
}

void assignFactoryValuesCompany(Factory* factory, const Company* company, const ProductionRecipe productionRecipe, const TransportNode location)
{
	loadFactoryConstructor(factory, productionRecipe);

	factory->location = location;
	factory->processing_speed = 1;
	factory->leftover_production = 0.0;

	factory->employee_wages = 10;
	factory->max_employee_num = 100; // TODO make recipe specific
	factory->current_employee_num = 0;

	if (company == NULL)
	{
		factory->managementType = MANAGEMENT_NONE;
		factory->management = NULL;
	}
	else
	{
		factory->managementType = MANAGEMENT_COMPANY;
		factory->management = company;
	}

	Stockpile* tmp_arr = getInputs(productionRecipe);
	for (int i = 0; i < factory->stockpiles_in_num; i++) {
		assignStockpileValues(&factory->stockpiles_in[i], tmp_arr[i].product_type, 0);
		assignOrderValues(&factory->orders_in[i], factory, 0, 100); // TODO: DEF. PRICE
		factory->ordered_in[i] = 0;
	}

	tmp_arr = getOutputs(productionRecipe);
	for (int i = 0; i < factory->stockpiles_out_num; i++) {
		assignStockpileValues(&factory->stockpiles_out[i], tmp_arr[i].product_type, 0);
		assignOrderValues(&factory->orders_out[i], factory, 0, 100); // TODO: DEF. PRICE
		factory->ordered_out[i] = 0;
	}

	assignHistoryArrayAvgValues(&factory->profit_history);
	factory->id = id_next++;
}

void assignFactoryValuesLocalPopulation(Factory* factory, const TransportNode location)
{
	const ProductionRecipe productionRecipe = Population_Consumption;
	loadFactoryConstructor(factory, productionRecipe);

	factory->location = location;
	factory->processing_speed = 1;
	factory->leftover_production = 0.0;

	factory->employee_wages = 10;
	factory->max_employee_num = 100; // TODO make recipe specific
	factory->current_employee_num = 0;

	factory->managementType = MANAGEMENT_LOCAL_POPULATION;
	factory->management = getLocalPopulationByLocation(factory->location);

	Stockpile* tmp_arr = getInputs(productionRecipe);
	for (int i = 0; i < factory->stockpiles_in_num; i++) {
		assignStockpileValues(&factory->stockpiles_in[i], tmp_arr[i].product_type, 0);
		assignOrderValues(&factory->orders_in[i], factory, 0, 100); // TODO: DEF. PRICE
		factory->ordered_in[i] = 0;
	}

	tmp_arr = getOutputs(productionRecipe);
	for (int i = 0; i < factory->stockpiles_out_num; i++) {
		assignStockpileValues(&factory->stockpiles_out[i], tmp_arr[i].product_type, 0);
		assignOrderValues(&factory->orders_out[i], factory, 0, 100); // TODO: DEF. PRICE
		factory->ordered_out[i] = 0;
	}

	assignHistoryArrayAvgValues(&factory->profit_history);
	factory->id = id_next++;
}

void loadFactoryConstructor(Factory* factory, const ProductionRecipe productionRecipe)
{
	factory->productionRecipe = productionRecipe;
	
	factory->stockpiles_in_num = getNumOfInputs(productionRecipe);
	factory->stockpiles_out_num = getNumOfOutputs(productionRecipe);

	factory->stockpiles_in = (Stockpile*) realloc(factory->stockpiles_in, factory->stockpiles_in_num * sizeof(Stockpile));
	factory->stockpiles_out = (Stockpile*) realloc(factory->stockpiles_out, factory->stockpiles_out_num * sizeof(Stockpile));

	factory->orders_in = (Order*) realloc(factory->orders_in, factory->stockpiles_in_num * sizeof(Order));
	factory->orders_out = (Order*) realloc(factory->orders_out, factory->stockpiles_out_num * sizeof(Order));

	factory->ordered_in = (QUANTITY_INT*) realloc(factory->ordered_in, factory->stockpiles_in_num * sizeof(QUANTITY_INT));
	factory->ordered_out = (QUANTITY_INT*) realloc(factory->ordered_out, factory->stockpiles_out_num * sizeof(QUANTITY_INT));
}

void assignLoadIdFactory(Factory* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

QUANTITY_INT* getOrderedInQuantity(const Factory* factory, const Product product)
{
	for (int i = 0; i < factory->stockpiles_in_num; i++)
	{
		if (factory->stockpiles_in[i].product_type == product)
		{
			return &factory->ordered_in[i];
		}
	}
	return NULL;
}

QUANTITY_INT* getOrderedOutQuantity(const Factory* factory, const Product product)
{
	for (int i = 0; i < factory->stockpiles_out_num; i++)
	{
		if (factory->stockpiles_out[i].product_type == product)
		{
			return &factory->ordered_out[i];
		}
	}
	return NULL;
}

void addOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
	QUANTITY_INT* result = getOrderedInQuantity(factory, product);
	if (result != NULL)
	{
		if (QUANTITY_INT_MAX - quantity >= *result)
		{
			(*result) += quantity;
		}
	}
}

void addOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
	QUANTITY_INT* result = getOrderedOutQuantity(factory, product);
	if (result != NULL)
	{
		if (QUANTITY_INT_MAX - quantity >= *result)
		{
			(*result) += quantity;
		}
	}
}

void removeOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
	QUANTITY_INT* result = getOrderedInQuantity(factory, product);
	if (result != NULL)
	{
		if (*result >= quantity)
		{
			(*result) -= quantity;
		}
	}
}

void removeOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
	QUANTITY_INT* result = getOrderedOutQuantity(factory, product);
	if (result != NULL)
	{
		if (*result >= quantity)
		{
			(*result) -= quantity;
		}
	}
}

// TODO TBU
void addEmployees(Factory* factory, const int employees)
{
	if (factory->current_employee_num + employees > factory->max_employee_num) { return; }
	factory->current_employee_num += employees;
}

// TODO TBU
void removeEmployees(Factory* factory, const int employees)
{
	// if (factory->current_employee_num - employees < 0) { return; } // SHOULD NEVER HAPPEN
	factory->current_employee_num -= employees;
}

// TODO smooth out and standardise the recording process
void insertFundsFactory(Factory* factory, const int funds)
{
	switch (factory->managementType)
	{
		case MANAGEMENT_COMPANY:
			insertFundsCompany((Company*)factory->management, funds);
			recordInsertFundsFactory(factory, funds);
			break;
		case MANAGEMENT_LOCAL_POPULATION:
			insertFundsLocalPopulation((LocalPopulation*)factory->management, funds);
			break;
		case MANAGEMENT_NONE:
			return;
	}
}

// TODO smooth out and standardise the recording process
// TODO check funds are avaliable
void withdrawFundsFactory(Factory* factory, const int funds)
{
	switch (factory->managementType)
	{
		case MANAGEMENT_COMPANY:
			withdrawFundsCompany((Company*)factory->management, funds);
			recordWithdrawFundsFactory(factory, funds);
			break;
		case MANAGEMENT_LOCAL_POPULATION:
			withdrawFundsLocalPopulation((LocalPopulation*)factory->management, funds);
			break;
		case MANAGEMENT_NONE:
			return;
	}
}

void recordInsertFundsFactory(Factory* factory, const int funds)
{
	addToHistoryArrayAvg(&factory->profit_history, funds);
}

void recordWithdrawFundsFactory(Factory* factory, const int funds)
{
	subFromHistoryArrayAvg(&factory->profit_history, funds);
}

void __processProductionTick(Factory* factory)
{
	// Get the most the factory can make
	float max_processing_speed = 
		(float)factory->processing_speed 
		* ((float)factory->current_employee_num / (float)factory->max_employee_num)
		+ factory->leftover_production;
	for (int i = 0; i < factory->stockpiles_in_num; i++) 
	{
		if (factory->stockpiles_in[i].quantity < max_processing_speed * getCost(factory->productionRecipe, factory->stockpiles_in[i].product_type))
		{
			max_processing_speed = factory->stockpiles_in[i].quantity / getCost(factory->productionRecipe, factory->stockpiles_in[i].product_type);
		}
	}

	uint_fast16_t next_processing_speed = (int) max_processing_speed;
	factory->leftover_production = max_processing_speed - next_processing_speed;
	factory->leftover_production = (float)(factory->leftover_production - (int) factory->leftover_production); // Equivalent to (X % 1)

	// Process the production steps
	for (int i = 0; i < factory->stockpiles_in_num; i++) 
	{
		processTickStockpile(&factory->stockpiles_in[i]);
		removeQuantity(&factory->stockpiles_in[i], next_processing_speed * getCost(factory->productionRecipe, factory->stockpiles_in[i].product_type));
	}

	for (int i = 0; i < factory->stockpiles_out_num; i++) 
	{
		processTickStockpile(&factory->stockpiles_out[i]);
		addQuantity(&factory->stockpiles_out[i], next_processing_speed * getResult(factory->productionRecipe, factory->stockpiles_out[i].product_type));
	}
}

void __processWagePaymentTick(Factory* factory)
{
	if (wage_tick_index == 0)
	{
		const int wage_payment = factory->employee_wages * factory->current_employee_num;
		withdrawFundsFactory(factory, wage_payment);
		insertFundsLocalPopulation(
			getLocalPopulationByLocation(factory->location),
			wage_payment
		);
	}
}

// TODO make better
void processTickFactoryStatic(void)
{
	wage_tick_index++;
	wage_tick_index %= WAGE_TICK_RATE;
}

void processTickFactory(Factory* factory)
{
	tickHistoryArrayAvgIndex(&factory->profit_history);

	__processProductionTick(factory);
	__processWagePaymentTick(factory);
}

void cleanFactory(Factory* factory) {
	for (int i = 0; i < factory->stockpiles_in_num; i++) {
		cleanStockpile(&(factory->stockpiles_in[i]));
		cleanOrder(&(factory->orders_in[i]));
	}
	free(factory->stockpiles_in);
	free(factory->orders_in);

	for (int i = 0; i < factory->stockpiles_out_num; i++) {
		cleanStockpile(&factory->stockpiles_out[i]);
		cleanOrder(&(factory->orders_out[i]));
	}
	free(factory->stockpiles_out);
	free(factory->orders_out);

	free(factory->ordered_in);
	free(factory->ordered_out);

	cleanHistoryArrayAvg(&factory->profit_history);
}
