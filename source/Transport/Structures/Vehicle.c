#include "Vehicle.h"

/*
TODO: MUST WORK AROUND LEFT-OVER QUANTITY
*/
inline void assignPickup(Vehicle* vehicle, const Factory* factory, const Product product)
{
    vehicle->end_factory = factory;
    vehicle->end_location = factory->location;
    vehicle->stockpile.quantity = 0; // TODO
    vehicle->stockpile.product_type = product;
}

inline void assignDelivery(Vehicle* vehicle, const Factory* factory)
{
    vehicle->end_factory = factory;
    vehicle->end_location = factory->location;
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

    vehicle->distance_travelled = dist_to_travel;
}

inline uint_fast16_t getVehiclesNextDistance(const Vehicle* vehicle)
{
    getNextDistance(vehicle->current_location, vehicle->end_location);
}

inline void moveVehicleToNextLoc(Vehicle* vehicle)
{
    vehicle->current_location = getNext(vehicle->current_location, vehicle->end_location);
    vehicle->distance_travelled = 0;
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
            }
            // Fail
        }
    }
    // Fail
}

void unloadCargo(Vehicle* vehicle, const Factory* factory)
{
    for (int i = 0; i < factory->stockpiles_in_num; i++) 
    {
        if (factory->stockpiles_in[i].product_type == vehicle->stockpile.product_type) 
        {
            if (QUANTITY_INT_MAX - factory->stockpiles_in[i].quantity >= vehicle->stockpile.quantity)
            {
                moveStockpile(&factory->stockpiles_in[i], &vehicle->stockpile, vehicle->stockpile.quantity);
            }
            else 
            {
                moveStockpile(&factory->stockpiles_in[i], &vehicle->stockpile, QUANTITY_INT_MAX - factory->stockpiles_in[i].quantity);
            }
        }
    }
    // Fail
}

inline void processTickVehicle(Vehicle* vehicle)
{
    if (vehicle->end_factory)
    {
        if (vehicle->current_location != vehicle->end_location)
        {
            stepToNextLocation(vehicle);
        }
        else if (vehicle->stockpile.quantity)
        {
            unloadCargo(vehicle, vehicle->end_factory);
            vehicle->end_factory = NULL;
        }
        else
        {
            loadCargo(vehicle, vehicle->end_factory, vehicle->stockpile.product_type);
            vehicle->end_factory = NULL;
            // Wait to be told where to deliver goods
        }
    }
}

void cleanVehicle(Vehicle* vehicle)
{
    // Nothing yet...
}

