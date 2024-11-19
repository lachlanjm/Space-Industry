#ifndef GOVERNMENT_H
#define GOVERNMENT_H

typedef struct Government Government;

#include <stdint.h>

#define GOVERNMENT_ID_INT uint_least16_t

struct Government {
	int wealth;

	int controlled_local_population_num;

	GOVERNMENT_ID_INT id;
};

#include "..\..\Environment\Enums\TransportNode.h"
#include "LocalPopulation.h"

#include <stdlib.h>

void setGovernmentControlStatic(const int transport_node_count);
Government* getGovernmentByLocation(const TransportNode location);
void setGovernmentControlByLocation(Government* government, const TransportNode location);
void resetGovernmentControlByLocation(const TransportNode location);
void cleanGovernmentControlStatic(void);

void assignGovernmentValues(Government* government, const int wealth);
void assignLoadIdGovernment(Government* obj, const int id);

void insertFundsGovernment(Government* government, const int funds);
void withdrawFundsGovernment(Government* government, const int funds);

void processTickGovernment(Government* government);

void cleanGovernment(Government* government);

#endif