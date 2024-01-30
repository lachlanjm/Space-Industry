#ifndef FACTORY_MANAGER_H
#define FACTORY_MANAGER_H

#include "..\..\Environment\Structures\MarketMap.h"
#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Production\Structures\Factory.h"

#include <stdint.h>

#define FACTORY_MANAGER_ID_INT uint_least16_t

// TODO: TBU finetune AI
#define STOCKPILE_FULL 500
#define DESIRED_STOCKPILE_MAX 350 // !!MUST BE!! < STOCKPILE_FULL - ORDER_QUANTITY_MIN
#define DESIRED_STOCKPILE_MIN 150
#define ORDER_QUANTITY_MIN 100

#define INCREASE_PRICE_FACTOR 1.25f
#define DECREASE_PRICE_FACTOR 0.875f

typedef struct FactoryManager {
	Factory controlled_factory;

	FACTORY_MANAGER_ID_INT id;
} FactoryManager;

void assignFactoryManagerValues(FactoryManager* factoryManager, const ProductionRecipe productionRecipe, const TransportNode location);

void updateOfferedPrices(FactoryManager* factoryManager);
void loadFactoryManagerAssignOrders(FactoryManager* factoryManager);

void processTickFactoryManager(FactoryManager* factoryManager);

void cleanFactoryManager(FactoryManager* factoryManager);

#endif