#ifndef FACTORY_MANAGER_H
#define FACTORY_MANAGER_H

#include "..\..\Environment\Structures\MarketMap.h"
#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Production\Structures\Factory.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define FACTORY_MANAGER_ID_INT uint_least16_t

// TODO: TBU finetune AI
#define FM_STOCKPILE_FULL 500
#define FM_DESIRED_SELL_STOCKPILE_ROOT 18.6 // !!MUST BE!! < STOCKPILE_FULL - ORDER_QUANTITY_MIN
#define FM_DESIRED_BUY_STOCKPILE_ROOT 12.3
#define FM_ORDER_QUANTITY_MIN 100

#define FM_DEFAULT_PRICE 30

typedef struct FactoryManager {
	Factory controlled_factory;

	FACTORY_MANAGER_ID_INT id;
} FactoryManager;

void assignFactoryManagerValues(FactoryManager* factoryManager, const ProductionRecipe productionRecipe, const TransportNode location);

void updateOfferedPrices(FactoryManager* factoryManager);
void loadFactoryManagerAssignOrders(FactoryManager* factoryManager);
void assignLoadIdFactoryManager(FactoryManager* obj, const int id);

void processTickFactoryManager(FactoryManager* factoryManager);

void cleanFactoryManager(FactoryManager* factoryManager);

#endif