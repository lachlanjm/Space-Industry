#ifndef COMPANY_H
#define COMPANY_H

typedef struct Company Company;

#define COMPANY_ID_INT uint_least16_t

#include "..\..\Production\Structures\Factory.h"

struct Company {
	int controlled_factories_num;
	int* deficit_ticks;
	Factory** controlled_factories;

	uint64_t wealth;

	COMPANY_ID_INT id;
};

#include "..\..\Environment\Structures\MarketMap.h"
#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\..\Helpers\GeneralHelpers.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>

// TODO: TBU finetune AI
#define CO_EMPLOYEE_DELTA_FACTOR 0.05f

// TODO: TBU finetune AI
#define CO_STOCKPILE_FULL 500
#define CO_DESIRED_SELL_STOCKPILE_ROOT 18.6 // !!MUST BE!! < STOCKPILE_FULL - ORDER_QUANTITY_MIN
#define CO_DESIRED_BUY_STOCKPILE_ROOT 12.3
#define CO_ORDER_QUANTITY_MIN 100

#define CO_NEW_FACTORY_MATERIAL_COST 1000000
#define CO_NEW_FACTORY_LABOR_COST 1000000
#define CO_NEW_FACTORY_MIN_RETURN 10 // per prod. tick, exclusive
#define CO_DESTROY_FACTORY_TICKS 10000

#define CO_MIN_PROFIT 100

#define CO_DEFAULT_PRICE 10

void assignNewCompanyValues(Company* const company);
void addNewFactoryToCompany(Company* const company, const ProductionRecipe productionRecipe, const TransportNode location);
Factory* loadAddNewFactoryToCompany(Company* const company);

void insertFundsCompany(Company* const company, const int funds);
void withdrawFundsCompany(Company* const company, const int funds);

void loadCompanyAssignOrders(Company* const company);
void assignLoadIdCompany(Company* const obj, const int id);

void processTickCompany(Company* const company);
void processBuildingTickCompany(Company* const company);

void cleanCompany(Company* company);

#endif