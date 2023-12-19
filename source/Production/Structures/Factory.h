#ifndef FACTORY_H
#define FACTORY_H

#include "..\Enums\ProductionRecipe.h"
#include "..\Structures\Stockpile.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Transport\Enums\TransportNode.h"

typedef struct Factory
{
    ProductionRecipe productionRecipe;
    TransportNode location;

    uint_fast8_t stockpiles_in_num;
    uint_fast8_t stockpiles_out_num;
    uint_fast16_t processing_speed; // TODO TBU
    
    Stockpile* stockpiles_in;
    Stockpile* stockpiles_out;

    Order* orders_in;
    Order* orders_out;

} Factory;

Factory* newFactory(const ProductionRecipe productionRecipe, const TransportNode location);
void assignFactoryValues(Factory* factory, const ProductionRecipe productionRecipe, const TransportNode location);

// TODO TBU
inline void processTickFactory(Factory* factory);

// DO NOT CLEAN ITEM (ONLY CONSTITUENTS)
void cleanFactory(Factory* factory);

#endif