#ifndef LOCAL_POPULATION_H
#define LOCAL_POPULATION_H

typedef struct LocalPopulation LocalPopulation;

#define LOCAL_POPULATION_ID_INT uint_least16_t

#include "..\..\Production\Structures\Factory.h"

struct LocalPopulation {
	uint32_t population_number;
	uint32_t employed_number;
	Factory population_centre;
	
	int wealth;

	// Government* controlling_government;
	LOCAL_POPULATION_ID_INT id;
};

#include "..\..\Environment\Enums\TransportNode.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Production\Enums\Product.h"
#include "..\..\Production\Structures\Stockpile.h"
#include "..\..\..\Helpers\GeneralHelpers.h"

#include <stdint.h>
#include <stdio.h>

#define CONSUMPTION_RATE_DIVISOR 100

// TODO: TBU finetune AI
#define LP_STOCKPILE_FULL 2000
#define LP_DESIRED_SELL_STOCKPILE_ROOT 18.6 // !!MUST BE!! < STOCKPILE_FULL - ORDER_QUANTITY_MIN
#define LP_DESIRED_BUY_STOCKPILE_ROOT 12.3
#define LP_ORDER_QUANTITY_MIN 100

#define LP_DEFAULT_PRICE 30
#define LP_MIN_PROFIT 100 // TODO TBU

void setTransportNodeCountLocalPopulationStatic(const int transport_node_count);
int getLocalPopulationNum(void);
LocalPopulation* getLocalPopulationByLocation(const TransportNode location);
void cleanTransportNodeCountLocalPopulationStatic(void);

void assignLocalPopulationValues(const TransportNode location, const uint32_t population_number);
void moveLocalPopulationToStaticArray(LocalPopulation* origin, const TransportNode location);
void assignLoadIdLocalPopulation(LocalPopulation* obj, const int id);
void loadLocalPopulationAssignOrders(LocalPopulation* population);

void insertFundsLocalPopulation(LocalPopulation* population, const int funds);
void withdrawFundsLocalPopulation(LocalPopulation* population, const int funds);

IND_BOOL increaseEmployedLocalPopulation(LocalPopulation* population, const int jobs);
IND_BOOL decreaseEmployedLocalPopulation(LocalPopulation* population, const int jobs);

void processTickLocalPopulation(LocalPopulation* population);
void updateLocalPopulationOfferedPrices(LocalPopulation* population);

void cleanLocalPopulation(LocalPopulation* population);

#endif