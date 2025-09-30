#ifndef TRANSPORT_MAP_H
#define TRANSPORT_MAP_H

#include "..\Enums\TransportNode.h"
#include "..\..\Transport\Structures\Vehicle.h"
#include "..\..\Management\Logistics\LogisticsManager.h"

void instantiateNewTransportMap(const int location_num);

void appendFreeHook(VehicleLocationHook* const hook, const TransportNode location);
void appendBusyHook(VehicleLocationHook* const hook, const TransportNode location);

VehicleLocationHook* getNextFreeHookAt(const TransportNode location);
LogisticsManager* getNextFreeManagerAt(const TransportNode location);
Vehicle* getNextFreeVehicleAt(const TransportNode location);

void moveFreeVehicleHookTo(VehicleLocationHook* const hook, const TransportNode location);
void moveBusyVehicleHookTo(VehicleLocationHook* const hook, const TransportNode location);

void cleanTransportMap(void);

#endif
