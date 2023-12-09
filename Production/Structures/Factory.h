#ifndef FACTORY_H
#define FACTORY_H

#include "..\Enums\ProductionRecipe.h"
#include "Stockpile.h"

typedef struct Factory
{
    ProductionRecipe productionRecipe;

    uint_fast8_t stockpiles_in_num;
    uint_fast8_t stockpiles_out_num;
    uint_fast16_t processing_speed; // TODO TBU
    
    Stockpile* stockpiles_in;
    Stockpile* stockpiles_out;

} Factory;

Factory* newFactory(const ProductionRecipe productionRecipe);
void assignFactoryValues(Factory* factory, const ProductionRecipe productionRecipe);

// TODO TBU
inline void processTick(Factory* factory);

// DO NOT CLEAN ITEM (ONLY CONSTITUENTS)
void clean(Factory* factory);

#endif