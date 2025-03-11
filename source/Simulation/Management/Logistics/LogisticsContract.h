#ifndef LOGISTICS_CONTRACT_H
#define LOGISTICS_CONTRACT_H

typedef struct LogisticsContract LogisticsContract;

#include "..\..\Transport\Structures\Vehicle.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\..\Production\Enums\Product.h"

#include <stdint.h>

#define LOGISTICS_CONTRACT_ID_INT uint_least16_t

enum ContractPhase {
	ASSIGNMENT,
	PICK_UP,
	DELIVERY,
	COMPLETED
};

struct LogisticsContract {
	// uint_fast16_t vehicle_num;
	Vehicle* assigned_vehicle; // TODO make array

	Factory* selling_factory;
	Factory* buying_factory;

	enum ContractPhase current_phase;
	Product product;
	QUANTITY_INT quantity;
	LOGISTICS_CONTRACT_ID_INT id;
};

LogisticsContract* newLogisticsContract(const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity);
void assignLogisticsContractValues(LogisticsContract* logisticsContract, const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const enum ContractPhase current_phase, const Product product, const QUANTITY_INT quantity);
void assignLoadIdLogisticsContract(LogisticsContract* obj, const int id);

int processTickLogisticsContract(LogisticsContract* const logisticsContract);
void cleanContract(LogisticsContract* logisticsContract);

#endif