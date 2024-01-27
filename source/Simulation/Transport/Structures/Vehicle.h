#ifndef VEHICLE_H
#define VEHICLE_H

#include "..\..\Production\Structures\Stockpile.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\..\Environment\Enums\TransportNode.h"
#include "..\..\Environment\Structures\Map.h"

#define VEHICLE_SPEED 1
#define VEHICLE_CAPACITY 100

typedef struct Vehicle {
	TransportNode current_location;
	TransportNode end_location;
	uint_fast16_t distance_travelled; // distance travelled from last node

	Stockpile stockpile;
	
	Factory* end_factory;
	QUANTITY_INT max_capacity;
	// TODO VehicleType type; (or so...)
} Vehicle;

void assignNewVehicleValues(Vehicle* vehicle, const TransportNode start_location);

void assignPickup(Vehicle* vehicle, const Factory* factory, const Product product);
void assignDelivery(Vehicle* vehicle, const Factory* factory);

void stepToNextLocation(Vehicle* vehicle);
void moveVehicleToNextLoc(Vehicle* vehicle);
uint_fast16_t getVehiclesNextDistance(const Vehicle* vehicle);

void loadCargo(Vehicle* vehicle, const Factory* factory, const Product product_type);
void unloadCargo(Vehicle* vehicle, const Factory* factory);

// TODO TBU
void processTickVehicle(Vehicle* vehicle);

// DON'T free item, only constituents
void cleanVehicle(Vehicle* vehicle);

#endif