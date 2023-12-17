#include "Factory.h"

Factory* newFactory(const ProductionRecipe productionRecipe)
{
    Factory* factory = (Factory*) malloc(1 * sizeof(Factory));

    factory->productionRecipe = productionRecipe;
    factory->processing_speed = 0;

    factory->stockpiles_in_num = getNumOfInputs(productionRecipe);
    factory->stockpiles_out_num = getNumOfOutputs(productionRecipe);

    factory->stockpiles_in = (Stockpile*) malloc(factory->stockpiles_in_num * sizeof(Stockpile));
    factory->stockpiles_out = (Stockpile*) malloc(factory->stockpiles_out_num * sizeof(Stockpile));

    Stockpile* tmp_arr = getInputs(productionRecipe);
    for (int i = 0; i < factory->stockpiles_in_num; i++) {
        assignStockpileValues(&factory->stockpiles_in[i], tmp_arr[i].product_type, 0);
    }

    tmp_arr = getOutputs(productionRecipe);
    for (int i = 0; i < factory->stockpiles_out_num; i++) {
        assignStockpileValues(&factory->stockpiles_out[i], tmp_arr[i].product_type, 0);
    }

    return factory;
}

void assignFactoryValues(Factory* factory, const ProductionRecipe productionRecipe)
{
    factory->productionRecipe = productionRecipe;
    factory->processing_speed = 0;

    factory->stockpiles_in_num = getNumOfInputs(productionRecipe);
    factory->stockpiles_out_num = getNumOfOutputs(productionRecipe);

    factory->stockpiles_in = (Stockpile*) malloc(factory->stockpiles_in_num * sizeof(Stockpile));
    factory->stockpiles_out = (Stockpile*) malloc(factory->stockpiles_out_num * sizeof(Stockpile));

    Stockpile* tmp_arr = getInputs(productionRecipe);
    for (int i = 0; i < factory->stockpiles_in_num; i++) {
        assignStockpileValues(&factory->stockpiles_in[i], tmp_arr[i].product_type, 0);
    }

    tmp_arr = getOutputs(productionRecipe);
    for (int i = 0; i < factory->stockpiles_out_num; i++) {
        assignStockpileValues(&factory->stockpiles_out[i], tmp_arr[i].product_type, 0);
    }
}

// TBU (CHECK FOR POSSIBLE, REVERT OTHERWISE)
inline void processTick(Factory* factory)
{
    for (int i = 0; i < factory->stockpiles_in_num; i++) {
        removeQuantity(&factory->stockpiles_in[i], factory->processing_speed * getCost(factory->productionRecipe, factory->stockpiles_in[i].product_type));
    }

    for (int i = 0; i < factory->stockpiles_out_num; i++) {
        addQuantity(&factory->stockpiles_out[i], factory->processing_speed * getResult(factory->productionRecipe, factory->stockpiles_out[i].product_type));
    }
}

void clean(Factory* factory) {
    for (int i = 0; i < factory->stockpiles_in_num; i++) {
        clean(&factory->stockpiles_in[i]);
    }
    free(factory->stockpiles_in);

    for (int i = 0; i < factory->stockpiles_out_num; i++) {
        clean(&factory->stockpiles_out[i]);
    }
    free(factory->stockpiles_out);
}
