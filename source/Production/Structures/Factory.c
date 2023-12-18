#include "Factory.h"

Factory* newFactory(const ProductionRecipe productionRecipe, const TransportNode location)
{
    Factory* factory = (Factory*) malloc(1 * sizeof(Factory));

    factory->productionRecipe = productionRecipe;
    factory->location = location;
    factory->processing_speed = 0;

    factory->stockpiles_in_num = getNumOfInputs(productionRecipe);
    factory->stockpiles_out_num = getNumOfOutputs(productionRecipe);

    factory->stockpiles_in = (Stockpile*) malloc(factory->stockpiles_in_num * sizeof(Stockpile));
    factory->stockpiles_out = (Stockpile*) malloc(factory->stockpiles_out_num * sizeof(Stockpile));

    factory->orders_in = (Order*) malloc(factory->stockpiles_in_num * sizeof(Order));
    factory->orders_out = (Order*) malloc(factory->stockpiles_out_num * sizeof(Order));

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

void assignFactoryValues(Factory* factory, const ProductionRecipe productionRecipe, const TransportNode location)
{
    factory->productionRecipe = productionRecipe;
    factory->location = location;
    factory->processing_speed = 0;

    factory->stockpiles_in_num = getNumOfInputs(productionRecipe);
    factory->stockpiles_out_num = getNumOfOutputs(productionRecipe);

    factory->stockpiles_in = (Stockpile*) realloc(factory->stockpiles_in, factory->stockpiles_in_num * sizeof(Stockpile));
    factory->stockpiles_out = (Stockpile*) realloc(factory->stockpiles_out, factory->stockpiles_out_num * sizeof(Stockpile));

    factory->orders_in = (Order*) realloc(factory->orders_in, factory->stockpiles_in_num * sizeof(Order));
    factory->orders_out = (Order*) realloc(factory->orders_out, factory->stockpiles_out_num * sizeof(Order));

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

void cleanFactory(Factory* factory) {
    for (int i = 0; i < factory->stockpiles_in_num; i++) {
        cleanStockpile(&(factory->stockpiles_in[i]));
        cleanOrder(&(factory->orders_in[i]));
    }
    free(factory->stockpiles_in);
    free(factory->orders_in);

    for (int i = 0; i < factory->stockpiles_out_num; i++) {
        cleanStockpile(&factory->stockpiles_out[i]);
        cleanOrder(&(factory->orders_out[i]));
    }
    free(factory->stockpiles_out);
    free(factory->orders_out);
}
