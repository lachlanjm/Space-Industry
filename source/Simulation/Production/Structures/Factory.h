#ifndef FACTORY_H
#define FACTORY_H

typedef struct Factory Factory;

#include "..\Enums\ProductionRecipe.h"
#include "..\Structures\Stockpile.h"
#include "..\..\Markets\Structures\Order.h"
#include "..\..\Environment\Enums\TransportNode.h"

typedef struct Factory
{
    ProductionRecipe productionRecipe;
    TransportNode location;

    uint_fast8_t stockpiles_in_num;
    uint_fast8_t stockpiles_out_num;
    uint_fast16_t processing_speed; // TODO TBU
    
    Stockpile* stockpiles_in;
    Stockpile* stockpiles_out;

    struct OrderDef* orders_in;
    struct OrderDef* orders_out;

    QUANTITY_INT* ordered_in;
    QUANTITY_INT* ordered_out;

} Factory;

Factory* newFactory(const ProductionRecipe productionRecipe, const TransportNode location);
void assignFactoryValues(Factory* factory, const ProductionRecipe productionRecipe, const TransportNode location);

QUANTITY_INT* getOrderedInQuantity(const Factory* factory, const Product product);
QUANTITY_INT* getOrderedOutQuantity(const Factory* factory, const Product product);

void addOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);
void addOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);
void removeOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);
void removeOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity);

// TODO TBU
void processTickFactory(Factory* factory);

// DO NOT CLEAN ITEM (ONLY CONSTITUENTS)
void cleanFactory(Factory* factory);

#endif