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
	uint_fast16_t assigned_vehicle_num; // placeholder
	Vehicle* assigned_vehicle; // TODO make array

	TransportNode pickup_location;
	TransportNode dropoff_location;
	
	Stockpile* pickup_stockpile;
	Stockpile* dropoff_stockpile;
	
	QUANTITY_INT* ordered_in_val;
	QUANTITY_INT* ordered_out_val;
	
	enum ContractPhase current_phase;
	Product product;
	QUANTITY_INT quantity;
	QUANTITY_INT quantity_unassigned;
	LOGISTICS_CONTRACT_ID_INT id;
};

LogisticsContract* newLogisticsContract(
	const Vehicle* assigned_vehicle,
	const TransportNode pickup_location,
	const TransportNode dropoff_location,
	Stockpile const* pickup_stockpile,
	Stockpile const* dropoff_stockpile,
	QUANTITY_INT const* ordered_in_val,
	QUANTITY_INT const* ordered_out_val,
	const Product product, 
	const QUANTITY_INT quantity
);
void assignLogisticsContractValues(LogisticsContract* logisticsContract, 
	const Vehicle* assigned_vehicle, 
	const TransportNode pickup_location,
	const TransportNode dropoff_location,
	Stockpile const* pickup_stockpile,
	Stockpile const* dropoff_stockpile,
	QUANTITY_INT const* ordered_in_val,
	QUANTITY_INT const* ordered_out_val,
	const enum ContractPhase current_phase, 
	const Product product, 
	const QUANTITY_INT quantity
);
void assignLoadIdLogisticsContract(LogisticsContract* obj, const int id);

int processTickLogisticsContract(LogisticsContract* const logisticsContract);
void cleanContract(LogisticsContract* logisticsContract);

#endif