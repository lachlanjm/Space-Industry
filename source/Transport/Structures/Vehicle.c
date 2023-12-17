#include "Vehicle.h"

inline void moveToNextLocation(Vehicle* vehicle, const TransportNode* transportNode)
{
    vehicle->current_location = transportNode;
    vehicle->current_location_type = TRANSPORT_NODE;
}

inline void moveToNextLocation(Vehicle* vehicle, const TransportConnection* transportConnection)
{
    vehicle->current_location = transportConnection;
    vehicle->current_location_type = TRANSPORT_CONNECTION;
}

inline void moveToNextLocation(Vehicle* vehicle, const Factory* factory)
{
    vehicle->current_location = factory;
    vehicle->current_location_type = FACTORY;
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

