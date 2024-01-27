#include "LogisticsContract.h"

LogisticsContract* newLogisticsContract(const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
	LogisticsContract* logisticsContract = (LogisticsContract*) malloc(1 * sizeof(LogisticsContract));
	assignNewLogisticsContractValues(logisticsContract, assigned_vehicle, selling_factory, buying_factory, ASSIGNMENT, product, quantity);
	return logisticsContract;
}

void assignNewLogisticsContractValues(LogisticsContract* logisticsContract, const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const enum ContractPhase current_phase, const Product product, const QUANTITY_INT quantity)
{
	logisticsContract->assigned_vehicle = assigned_vehicle;
	logisticsContract->selling_factory = selling_factory;
	logisticsContract->buying_factory = buying_factory;
	logisticsContract->current_phase = current_phase;
	logisticsContract->product = product;
	logisticsContract->quantity = quantity;
}

/*
TODO: ACCOUNT FOR END FACTORY diff END LOCATION
*/
int processTickLogisticsContract(LogisticsContract* logisticsContract)
{
	switch (logisticsContract->current_phase)
	{
	case ASSIGNMENT:
		assignPickup(logisticsContract->assigned_vehicle, logisticsContract->selling_factory, logisticsContract->product);
		logisticsContract->assigned_vehicle->max_capacity = logisticsContract->quantity; // TODO: VEHICLE MAX CAP
		logisticsContract->current_phase = PICK_UP;
	case PICK_UP:
		if (logisticsContract->assigned_vehicle->current_location == logisticsContract->assigned_vehicle->end_location)
		{
			loadCargo(logisticsContract->assigned_vehicle, logisticsContract->selling_factory, logisticsContract->product);
			removeOrderedOutQuantity(logisticsContract->selling_factory, logisticsContract->product, logisticsContract->quantity);
			assignDelivery(logisticsContract->assigned_vehicle, logisticsContract->buying_factory);
			logisticsContract->current_phase = DELIVERY;
		}
		else
		{
			return 0;
		}
	case DELIVERY:
		if (logisticsContract->assigned_vehicle->current_location == logisticsContract->assigned_vehicle->end_location)
		{
			unloadCargo(logisticsContract->assigned_vehicle, logisticsContract->buying_factory);
			removeOrderedInQuantity(logisticsContract->buying_factory, logisticsContract->product, logisticsContract->quantity);
			logisticsContract->assigned_vehicle->end_factory = NULL;
			logisticsContract->assigned_vehicle->end_location = -1;
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
