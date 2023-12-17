#ifndef VEHICLE_H
#define VEHICLE_H

#include "..\..\Production\Structures\Stockpile.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\Enums\TransportNode.h"
#include "..\Enums\TransportConnectionType.h"

typedef struct Vehicle {
    Stockpile stockpile;

    void* current_location;
    QUANTITY_INT max_capacity;

} Vehicle;

inline void moveToNextLocation(Vehicle* vehicle, const TransportNode* transportNode);
inline void moveToNextLocation(Vehicle* vehicle, const TransportConnection* transportConnection);
inline void moveToNextLocation(Vehicle* vehicle, const Factory* factory);

void loadCargo(Vehicle* vehicle, const Factory* factory, const Product product_type);
void unloadCargo(Vehicle* vehicle, const Factory* factory);

#endif