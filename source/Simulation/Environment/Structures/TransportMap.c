#include "TransportMap.h"

static VehicleLocationHook* __vehicle_hook_free_map__ = NULL;
static VehicleLocationHook* __vehicle_hook_busy_map__ = NULL;

void instantiateNewTransportMap(const int location_num)
{
	__vehicle_hook_free_map__ = calloc(location_num, sizeof(VehicleLocationHook));
	__vehicle_hook_busy_map__ = calloc(location_num, sizeof(VehicleLocationHook));
	
	if (__vehicle_hook_free_map__ == NULL) return;
	if (__vehicle_hook_busy_map__ == NULL) return;

	for (int i=0; i < location_num; i++)
	{
		__vehicle_hook_free_map__[i].manager = NULL;
		__vehicle_hook_free_map__[i].vehicle = NULL;
		__vehicle_hook_free_map__[i].next = NULL;
		__vehicle_hook_free_map__[i].prev = NULL;

		__vehicle_hook_busy_map__[i].manager = NULL;
		__vehicle_hook_busy_map__[i].vehicle = NULL;
		__vehicle_hook_busy_map__[i].next = NULL;
		__vehicle_hook_busy_map__[i].prev = NULL;
	}
}

void appendFreeHook(VehicleLocationHook* const hook, const TransportNode location)
{
	VehicleLocationHook* curr_hook = &__vehicle_hook_free_map__[location];

	while (curr_hook->next != NULL) {curr_hook = curr_hook->next;}

	curr_hook->next = hook;
	hook->prev = curr_hook;
	hook->next = NULL;
}

void appendBusyHook(VehicleLocationHook* const hook, const TransportNode location)
{
	VehicleLocationHook* curr_hook = &__vehicle_hook_busy_map__[location];
	
	while (curr_hook->next != NULL) {curr_hook = curr_hook->next;}
	
	curr_hook->next = hook;
	hook->prev = curr_hook;
	hook->next = NULL;
}

VehicleLocationHook* getNextFreeHookAt(const TransportNode location)
{
	return __vehicle_hook_free_map__[location].next;
}

LogisticsManager* getNextFreeManagerAt(const TransportNode location)
{
	VehicleLocationHook* const hook = getNextFreeHookAt(location);
	if (hook == NULL) { return NULL; }
	return hook->manager;
}

Vehicle* getNextFreeVehicleAt(const TransportNode location)
{
	VehicleLocationHook* const hook = getNextFreeHookAt(location);
	if (hook == NULL) { return NULL; }
	return hook->vehicle;
}

void moveFreeVehicleHookTo(VehicleLocationHook* const hook, const TransportNode location)
{
	// There are stub roots
	hook->prev->next = hook->next;
	if (hook->next != NULL) { hook->next->prev = hook->prev; }

	appendFreeHook(hook, location);
}

void moveBusyVehicleHookTo(VehicleLocationHook* const hook, const TransportNode location)
{
	// There are stub roots
	hook->prev->next = hook->next;
	if (hook->next != NULL) { hook->next->prev = hook->prev; }
	
	appendBusyHook(hook, location);
}

void cleanTransportMap(void)
{
	free(__vehicle_hook_free_map__);
	free(__vehicle_hook_busy_map__);
}