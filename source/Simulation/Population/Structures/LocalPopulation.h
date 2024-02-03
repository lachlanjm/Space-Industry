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

typedef struct LocalPopulation {
	uint32_t population_number;
	Factory population_centre;

	// Government* controlling_government;
	LOCAL_POPULATION_ID_INT id;
} LocalPopulation;

LocalPopulation* newLocalPopulation(const TransportNode location, const uint32_t population_number);
void assignLocalPopulationValues(LocalPopulation* population, const TransportNode location, const uint32_t population_number);
void assignLoadIdLocalPopulation(LocalPopulation* obj, const int id);

void processTickLocalPopulation(LocalPopulation* population);

void cleanLocalPopulation(LocalPopulation* population);

#endif