#include "LogisticsContract.h"

static LOGISTICS_CONTRACT_ID_INT id_next = 0;
LogisticsContract* newLogisticsContract(const Vehicle* assigned_vehicle, const TransportNode pickup_location, const TransportNode dropoff_location, Stockpile const* pickup_stockpile, Stockpile const* dropoff_stockpile, QUANTITY_INT const* ordered_in_val, QUANTITY_INT const* ordered_out_val, const Product product, const QUANTITY_INT quantity)
{
	LogisticsContract* logisticsContract = (LogisticsContract*) calloc(1, sizeof(LogisticsContract));
	assignLogisticsContractValues(logisticsContract, assigned_vehicle, pickup_location, dropoff_location, pickup_stockpile, dropoff_stockpile, ordered_in_val, ordered_out_val, ASSIGNMENT, product, quantity);
	return logisticsContract;
}

void assignLogisticsContractValues(LogisticsContract* logisticsContract, const Vehicle* assigned_vehicle, const TransportNode pickup_location, const TransportNode dropoff_location, Stockpile const* pickup_stockpile, Stockpile const* dropoff_stockpile, QUANTITY_INT const* ordered_in_val, QUANTITY_INT const* ordered_out_val, const enum ContractPhase current_phase, const Product product, const QUANTITY_INT quantity)
{
	logisticsContract->assigned_vehicle = assigned_vehicle;
	
	logisticsContract->pickup_location = pickup_location;
	logisticsContract->dropoff_location = dropoff_location;
	logisticsContract->pickup_stockpile = pickup_stockpile;
	logisticsContract->dropoff_stockpile = dropoff_stockpile;
	logisticsContract->ordered_in_val = ordered_in_val;
	logisticsContract->ordered_out_val = ordered_out_val;

	logisticsContract->current_phase = current_phase;
	logisticsContract->product = product;
	logisticsContract->quantity = quantity;
	logisticsContract->quantity_unassigned = quantity;
	logisticsContract->id = id_next++;
}

void assignLoadIdLogisticsContract(LogisticsContract* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}


/*
TODO: ACCOUNT FOR END FACTORY diff END LOCATION
*/
int processTickLogisticsContract(LogisticsContract* const logisticsContract)
{
	Vehicle* const assigned_vehicle = logisticsContract->assigned_vehicle;
	switch (logisticsContract->current_phase)
	{
	case ASSIGNMENT:
		assignPickup(assigned_vehicle, logisticsContract->pickup_location, logisticsContract->product);
		assigned_vehicle->max_capacity = logisticsContract->quantity; // TODO: VEHICLE MAX CAP
		logisticsContract->quantity_unassigned = MAX(0, logisticsContract->quantity_unassigned - assigned_vehicle->max_capacity);
		logisticsContract->current_phase = PICK_UP;
	case PICK_UP:
		if (assigned_vehicle->current_location == assigned_vehicle->end_location)
		{
			if (loadCargo(assigned_vehicle, logisticsContract->pickup_stockpile, logisticsContract->product)) return 0;
			
			if (logisticsContract->ordered_out_val != NULL)
			{
				if (*logisticsContract->ordered_out_val >= assigned_vehicle->stockpile.quantity) // TODO make better
				{
					*logisticsContract->ordered_out_val -= assigned_vehicle->stockpile.quantity;
				}
			}

			assignDelivery(assigned_vehicle, logisticsContract->dropoff_location);
			logisticsContract->current_phase = DELIVERY;
		}
		else
		{
			return 0;
		}
	case DELIVERY:
		if (assigned_vehicle->current_location == assigned_vehicle->end_location)
		{
			if (unloadCargo(assigned_vehicle, logisticsContract->dropoff_stockpile)) return 0;

			if (logisticsContract->ordered_out_val != NULL)
			{
				if (*logisticsContract->ordered_in_val >= assigned_vehicle->stockpile.quantity) // TODO make better
				{
					*logisticsContract->ordered_in_val -= assigned_vehicle->stockpile.quantity;
				}
			}

			assigned_vehicle->end_location = -1;
			logisticsContract->current_phase = COMPLETED;
		}
		else
		{
			return 0;
		}
	case COMPLETED:
		/* do nothing until later */
		return 1;
	
	default:
		/* error */
		return 1;
	}
}

void cleanContract(LogisticsContract* logisticsContract)
{

}
