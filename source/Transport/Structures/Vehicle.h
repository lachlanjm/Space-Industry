#ifndef VEHICLE_H
#define VEHICLE_H

#include "..\..\Production\Structures\Stockpile.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\Enums\TransportNode.h"
#include "Map.h"

#define VEHICLE_SPEED 1

typedef struct Vehicle {
    TransportNode current_location;
    TransportNode end_location;
    uint_fast16_t distance_travelled; // distance travelled from last node

    Stockpile stockpile;
    
    Factory* end_factory;
    QUANTITY_INT max_capacity;
    // TODO VehicleType type; (or so...)
} Vehicle;

inline void assignPickup(Vehicle* vehicle, const Factory* factory, const Product product);
inline void assignDelivery(Vehicle* vehicle, const Factory* factory);

void stepToNextLocation(Vehicle* vehicle);
inline uint_fast16_t getVehiclesNextDistance(const Vehicle* veh);
inline void moveVehicleToNextLoc(Vehicle* vehicle);

void loadCargo(Vehicle* vehicle, const Factory* factory, const Product product_type);
void unloadCargo(Vehicle* vehicle, const Factory* factory);

// TODO TBU
inline void processTick(Vehicle* vehicle);

// DON'T free item, only constituents
void clean(Vehicle* vehicle);

#endif