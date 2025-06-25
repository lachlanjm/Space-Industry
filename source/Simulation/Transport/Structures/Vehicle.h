#ifndef VEHICLE_H
#define VEHICLE_H

typedef struct Vehicle Vehicle;
typedef struct VehicleLocationHook VehicleLocationHook;

#include "..\..\Production\Structures\Stockpile.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\..\Management\Logistics\LogisticsManager.h"
#include "..\..\Environment\Enums\TransportNode.h"

#include <stdint.h>

#define VEHICLE_ID_INT uint_least16_t

struct VehicleLocationHook {
	struct VehicleLocationHook* prev;
	struct VehicleLocationHook* next;

	struct Vehicle* vehicle;	
	LogisticsManager* manager;	
};

struct Vehicle {
	TransportNode current_location;
	TransportNode end_location;
	uint_fast16_t distance_travelled; // distance travelled from last node
	struct VehicleLocationHook location_hook;

	// TODO TBU remove stockpile def (use custom)
	Stockpile stockpile;
	
	QUANTITY_INT max_capacity;
	// TODO VehicleType type; (or so...)

	VEHICLE_ID_INT id;
};

#include "..\..\Environment\Structures\Map.h"

#define VEHICLE_SPEED 1
#define VEHICLE_CAPACITY 100

Vehicle* newVehicle(const TransportNode start_location);
void assignVehicleValues(Vehicle* vehicle, const TransportNode start_location);
void assignLoadIdVehicle(Vehicle* obj, const int id);

void assignPickup(Vehicle* vehicle, const TransportNode location, const Product product);
void assignDelivery(Vehicle* vehicle, const TransportNode location);

uint_fast16_t getVehiclesNextDistance(const Vehicle* vehicle);

int loadCargo(Vehicle* vehicle, Stockpile* stockpile, const Product product_type);
int unloadCargo(Vehicle* vehicle, Stockpile* stockpile);

// TODO TBU
void processTickVehicle(Vehicle* vehicle);

// DON'T free item, only constituents
void cleanVehicle(Vehicle* vehicle);

#endif