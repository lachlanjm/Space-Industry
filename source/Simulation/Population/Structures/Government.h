#ifndef GOVERNMENT_H
#define GOVERNMENT_H

typedef struct Government Government;

#include <stdint.h>

#define GOVERNMENT_ID_INT uint_least16_t

struct Government {
	int wealth;
	int32_t gst_rate; // [0%, 100%]:10^-3%

	int32_t* export_tariffs; // [-inf%, inf%] 10^-3%
	int32_t* import_tariffs; // [-inf%, inf%] 10^-3%

	int controlled_local_population_num;

	GOVERNMENT_ID_INT id;
};

#include "..\..\Environment\Enums\TransportNode.h"
#include "LocalPopulation.h"

#include <stdlib.h>

void setGovernmentCountStatic(const int _government_count);
int getGovernmentNum(void);
Government* getGovernmentByIndex(const int index);

void setGovernmentControlStatic(const int transport_node_count);
Government* getGovernmentByLocation(const TransportNode location);
void setGovernmentControlByLocation(Government* government, const TransportNode location);
void resetGovernmentControlByLocation(const TransportNode location);
void cleanGovernmentStatic(void);

int32_t getExportTaxRate(const Product product, const TransportNode from, const TransportNode to);
int32_t getGstTaxRate(const Product product, const TransportNode location);
int32_t getImportTaxRate(const Product product, const TransportNode from, const TransportNode to);

void assignGovernmentValues(Government* government, const int wealth);
void assignLoadIdGovernment(Government* obj, const int id);

void insertFundsGovernment(Government* government, const int funds);
void withdrawFundsGovernment(Government* government, const int funds);

void processTickAllGovernments(void);
void processTickGovernment(Government* government);

void cleanGovernment(Government* government);

#endif