#ifndef FACTORY_H
#define FACTORY_H

typedef struct Factory Factory;

#include "..\..\..\History\HistoryArrayAvg.h"
#include "..\Enums\ProductionRecipe.h"
#include "..\Structures\Stockpile.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Environment\Enums\TransportNode.h"

#define FACTORY_ID_INT uint_least16_t

typedef enum ManagementType {
	MANAGEMENT_NONE,
	MANAGEMENT_COMPANY,
	MANAGEMENT_LOCAL_POPULATION
} ManagementType;

struct Factory
{
	ProductionRecipe productionRecipe;
	TransportNode location;
	
	ManagementType managementType;
	void* management; // Company or LocalPopulation; depends on managementType

	uint_fast16_t processing_speed; // TODO TBU
	float leftover_production; // TODO set to more approriate value size; i.e. smaller than float

	uint_fast16_t employee_wages;
	uint_fast16_t current_employee_num;
	uint_fast16_t max_employee_num;

	HistoryArrayAvg profit_history;

	uint_fast8_t stockpiles_in_num;
	uint_fast8_t stockpiles_out_num;
	
	Stockpile* stockpiles_in;
	Stockpile* stockpiles_out;

	struct Order* orders_in;
	struct Order* orders_out;

	QUANTITY_INT* ordered_in;
	QUANTITY_INT* ordered_out;

	FACTORY_ID_INT id;
};

#include "..\..\Management\Production\Company.h"
#include "..\..\Population\Structures\LocalPopulation.h"

#include <stdio.h>

#define WAGE_TICK_RATE 64 // process ticks per wage tick

Factory* newFactory(const ProductionRecipe productionRecipe, const TransportNode location);
void assignFactoryValuesCompany(Factory* factory, const Company* company, const ProductionRecipe productionRecipe, const TransportNode location);
void assignFactoryValuesLocalPopulation(Factory* factory, const TransportNode location);

void loadFactoryConstructor(Factory* factory, const ProductionRecipe productionRecipe);
void assignLoadIdFactory(Factory* obj, const int id);
void reassignOrderOfferingPtrs(const Factory* factory);

QUANTITY_INT* getOrderedInQuantity(const Factory* factory, const Product product);
QUANTITY_INT* getOrderedOutQuantity(const Factory* factory, const Product product);

void addOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);
void addOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);
void removeOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);
void removeOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);

void addEmployees(Factory* factory, const int employees);
void removeEmployees(Factory* factory, const int employees);

void insertFundsFactory(Factory* factory, const int funds);
void withdrawFundsFactory(Factory* factory, const int funds);
void recordInsertFundsFactory(Factory* factory, const int funds);
void recordWithdrawFundsFactory(Factory* factory, const int funds);

// TODO TBU
void processTickFactoryStatic(void);
// TODO TBU
void processTickFactory(Factory* factory);

// DO NOT CLEAN ITEM (ONLY CONSTITUENTS)
void cleanFactory(Factory* factory);

#endif