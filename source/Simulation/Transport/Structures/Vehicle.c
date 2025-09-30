#include "Vehicle.h"

static VEHICLE_ID_INT id_next = 0;

Vehicle* newVehicle(const TransportNode start_location, LogisticsManager* const manager)
{
	Vehicle* vehicle = calloc(1, sizeof(Vehicle));
	assignVehicleValues(vehicle, start_location, manager);
	return vehicle;
}

void assignVehicleValues(Vehicle* const vehicle, const TransportNode start_location, LogisticsManager* const manager)
{
	vehicle->current_location = start_location;
	vehicle->end_location = -1;
	vehicle->distance_travelled = 0;
	
	vehicle->location_hook.next = NULL;
	vehicle->location_hook.prev = NULL;
	vehicle->location_hook.vehicle = vehicle;
	vehicle->location_hook.manager = manager;
	// Assumes vehicle is free upon creation 
	appendFreeHook(&vehicle->location_hook, vehicle->current_location);

	assignStockpileValues(&vehicle->stockpile, 0, 0);

	vehicle->max_capacity = VEHICLE_CAPACITY;

	vehicle->id = id_next++;
}

void assignLoadIdVehicle(Vehicle* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

/*
TODO: MUST WORK AROUND LEFT-OVER QUANTITY??
*/
void assignPickup(Vehicle* vehicle, const TransportNode location, const Product product)
{
	vehicle->end_location = location;
	vehicle->stockpile.quantity = 0; // TODO
	vehicle->stockpile.product_type = product;
}

void assignDelivery(Vehicle* vehicle, const TransportNode location)
{
	vehicle->end_location = location;
}

void moveVehicleToNextLoc(Vehicle* vehicle)
{
	vehicle->current_location = getNext(vehicle->current_location, vehicle->end_location);
	vehicle->distance_travelled = 0;

	// ASSUMES MOVEMENT IS ALWAYS FOR A BUSY REASON
	// Relies on the Manager/Contract to set to Free status by calling setVehicleStatusToFree()
	// Not done when vehicle gets to end loc as contract/job may still need the vehicle
	moveBusyVehicleHookTo(&vehicle->location_hook, vehicle->current_location); 
}

void stepToNextLocation(Vehicle* vehicle)
{
	uint_fast32_t dist_to_travel = VEHICLE_SPEED;
	while (
		dist_to_travel > 0 
		&& vehicle->current_location != vehicle->end_location
		&& vehicle->distance_travelled + dist_to_travel >= getVehiclesNextDistance(vehicle) 
	) {
		dist_to_travel -= getVehiclesNextDistance(vehicle) - vehicle->distance_travelled;
		moveVehicleToNextLoc(vehicle);
	}

	if (vehicle->current_location != vehicle->end_location && dist_to_travel > 0)
	{
		vehicle->distance_travelled += dist_to_travel;
	}
}

uint_fast16_t getVehiclesNextDistance(const Vehicle* vehicle)
{
	return getNextDistance(vehicle->current_location, vehicle->end_location);
}

int loadCargo(Vehicle* vehicle, Stockpile* stockpile, const Product product_type)
{
	if (vehicle->stockpile.quantity == 0)
	{
		setDiffProduct(&vehicle->stockpile, product_type);
		if (stockpile->quantity >= vehicle->max_capacity)
		{
			moveStockpile(stockpile, &vehicle->stockpile, vehicle->max_capacity);
		}
		else 
		{
			moveStockpile(stockpile, &vehicle->stockpile, stockpile->quantity);
		}
		return 0;
	}
	else if (vehicle->stockpile.product_type == product_type)
	{
		if (stockpile->quantity >= vehicle->max_capacity - product_type)
		{
			moveStockpile(stockpile, &vehicle->stockpile, vehicle->max_capacity - product_type);
		}
		else 
		{
			moveStockpile(stockpile, &vehicle->stockpile, stockpile->quantity);
		}
		return 0;
	}
	else return 1; // Fail
}

int unloadCargo(Vehicle* vehicle, Stockpile* stockpile)
{
	if (stockpile->product_type == vehicle->stockpile.product_type) 
	{
		if (QUANTITY_INT_MAX - stockpile->quantity >= vehicle->stockpile.quantity)
		{
			if (moveStockpile(&vehicle->stockpile, stockpile, vehicle->stockpile.quantity)) return 1;
		}
		else 
		{
			if (moveStockpile(&vehicle->stockpile, stockpile, QUANTITY_INT_MAX - stockpile->quantity)) return 1;
		}
		return 0;
	}
	else return 1; // Fail
}

void setVehicleStatusToFree(Vehicle* const vehicle)
{
	moveFreeVehicleHookTo(&vehicle->location_hook, vehicle->current_location);
}

void processTickVehicle(Vehicle* vehicle)
{
	if (vehicle->end_location != -1)
	{
		stepToNextLocation(vehicle);
	}
}

void cleanVehicle(Vehicle* vehicle)
{
	// Nothing yet...
}

