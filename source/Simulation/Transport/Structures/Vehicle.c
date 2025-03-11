#include "Vehicle.h"

static VEHICLE_ID_INT id_next = 0;

Vehicle* newVehicle(const TransportNode start_location)
{
	Vehicle* vehicle = calloc(1, sizeof(Vehicle));
	assignVehicleValues(vehicle, start_location);
	return vehicle;
}

void assignVehicleValues(Vehicle* vehicle, const TransportNode start_location)
{
	vehicle->current_location = start_location;
	vehicle->end_location = -1;
	vehicle->distance_travelled = 0;

	assignStockpileValues(&vehicle->stockpile, 0, 0);

	vehicle->end_factory = NULL;
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
void assignPickup(Vehicle* vehicle, const Factory* factory, const Product product)
{
	vehicle->end_factory = factory;
	vehicle->end_location = factory->location;
	vehicle->stockpile.quantity = 0; // TODO
	vehicle->stockpile.product_type = product;
}

void assignDelivery(Vehicle* vehicle, const Factory* factory)
{
	vehicle->end_factory = factory;
	vehicle->end_location = factory->location;
}

void moveVehicleToNextLoc(Vehicle* vehicle)
{
	vehicle->current_location = getNext(vehicle->current_location, vehicle->end_location);
	vehicle->distance_travelled = 0;
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

void loadCargo(Vehicle* vehicle, const Factory* factory, const Product product_type)
{
	for (int i = 0; i < factory->stockpiles_out_num; i++) 
	{
		if (factory->stockpiles_out[i].product_type == product_type) 
		{
			if (vehicle->stockpile.quantity == 0)
			{
				setDiffProduct(&vehicle->stockpile, product_type);
				if (factory->stockpiles_out[i].quantity >= vehicle->max_capacity)
				{
					moveStockpile(&factory->stockpiles_out[i], &vehicle->stockpile, vehicle->max_capacity);
				}
				else 
				{
					moveStockpile(&factory->stockpiles_out[i], &vehicle->stockpile, factory->stockpiles_out[i].quantity);
				}
				return;
			}
			else if (vehicle->stockpile.product_type == product_type)
			{
				if (factory->stockpiles_out[i].quantity >= vehicle->max_capacity - product_type)
				{
					moveStockpile(&factory->stockpiles_out[i], &vehicle->stockpile, vehicle->max_capacity - product_type);
				}
				else 
				{
					moveStockpile(&factory->stockpiles_out[i], &vehicle->stockpile, factory->stockpiles_out[i].quantity);
				}
				return;
			}
			// Fail
		}
	}
	// Fail
}

int unloadCargo(Vehicle* vehicle, const Factory* factory)
{
	for (int i = 0; i < factory->stockpiles_in_num; i++) 
	{
		if (factory->stockpiles_in[i].product_type == vehicle->stockpile.product_type) 
		{
			if (QUANTITY_INT_MAX - factory->stockpiles_in[i].quantity >= vehicle->stockpile.quantity)
			{
				if (moveStockpile(&vehicle->stockpile, &factory->stockpiles_in[i], vehicle->stockpile.quantity)) return 1;
			}
			else 
			{
				if (moveStockpile(&vehicle->stockpile, &factory->stockpiles_in[i], QUANTITY_INT_MAX - factory->stockpiles_in[i].quantity)) return 1;
			}
			return 0;
		}
	}
	return 1;
}

void processTickVehicle(Vehicle* vehicle)
{
	if (vehicle->end_factory)
	{
		stepToNextLocation(vehicle);
	}
}

void cleanVehicle(Vehicle* vehicle)
{
	// Nothing yet...
}

