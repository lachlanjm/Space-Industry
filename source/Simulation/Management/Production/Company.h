#ifndef COMPANY_H
#define COMPANY_H

typedef struct Company Company;

#define COMPANY_ID_INT uint_least16_t

#include "..\..\Production\Structures\Factory.h"

struct Company {
	Factory controlled_factory;

	int wealth;

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
#define CO_EMPLOYEE_DELTA_FACTOR 0.1f

// TODO: TBU finetune AI
#define CO_STOCKPILE_FULL 500
#define CO_DESIRED_SELL_STOCKPILE_ROOT 18.6 // !!MUST BE!! < STOCKPILE_FULL - ORDER_QUANTITY_MIN
#define CO_DESIRED_BUY_STOCKPILE_ROOT 12.3
#define CO_ORDER_QUANTITY_MIN 100

#define CO_MIN_PROFIT 100
#define CO_MIN_PROFIT_FACTOR_BUY 1.001
#define CO_MIN_PROFIT_FACTOR_SELL 1.002

#define CO_DEFAULT_PRICE 100

void assignCompanyValues(Company* company, const ProductionRecipe productionRecipe, const TransportNode location);

void insertFundsCompany(Company* company, const int funds);
void withdrawFundsCompany(Company* company, const int funds);

void loadCompanyAssignOrders(Company* company);
void assignLoadIdCompany(Company* obj, const int id);

void processTickCompany(Company* company);

void cleanCompany(Company* company);

#endif