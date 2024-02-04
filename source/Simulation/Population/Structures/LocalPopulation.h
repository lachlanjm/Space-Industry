#ifndef LOCAL_POPULATION_H
#define LOCAL_POPULATION_H

#include "..\..\Environment\Enums\TransportNode.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Production\Enums\Product.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\..\Production\Structures\Stockpile.h"

#include <stdint.h>

#define LOCAL_POPULATION_ID_INT uint_least16_t

#define CONSUMPTION_RATE_DIVISOR 1000

// TODO: TBU finetune AI
#define LP_STOCKPILE_FULL 500 // WITH PROC_SPEED==1
#define LP_DESIRED_STOCKPILE_MAX 400 // !!MUST BE!! < STOCKPILE_FULL - ORDER_QUANTITY_MIN
#define LP_DESIRED_STOCKPILE_MIN 200
#define LP_ORDER_QUANTITY_MIN 50

#define LP_INCREASE_PRICE_FACTOR 1.05f
#define LP_DECREASE_PRICE_FACTOR 0.96f

typedef struct LocalPopulation {
	uint32_t population_number;
	Factory population_centre;

	// Government* controlling_government;
	LOCAL_POPULATION_ID_INT id;
} LocalPopulation;

LocalPopulation* newLocalPopulation(const TransportNode location, const uint32_t population_number);
void assignLocalPopulationValues(LocalPopulation* population, const TransportNode location, const uint32_t population_number);
void assignLoadIdLocalPopulation(LocalPopulation* obj, const int id);
void loadLocalPopulationAssignOrders(LocalPopulation* population);

void processTickLocalPopulation(LocalPopulation* population);
void updateLocalPopulationOfferedPrices(LocalPopulation* population);

void cleanLocalPopulation(LocalPopulation* population);

#endif