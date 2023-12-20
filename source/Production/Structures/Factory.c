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

    factory->ordered_in = (QUANTITY_INT*) malloc(factory->stockpiles_in_num * sizeof(QUANTITY_INT));
    factory->ordered_out = (QUANTITY_INT*) malloc(factory->stockpiles_out_num * sizeof(QUANTITY_INT));

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

    factory->ordered_in = (QUANTITY_INT*) realloc(factory->ordered_in, factory->stockpiles_in_num * sizeof(QUANTITY_INT));
    factory->ordered_out = (QUANTITY_INT*) realloc(factory->ordered_out, factory->stockpiles_out_num * sizeof(QUANTITY_INT));

    Stockpile* tmp_arr = getInputs(productionRecipe);
    for (int i = 0; i < factory->stockpiles_in_num; i++) {
        assignStockpileValues(&factory->stockpiles_in[i], tmp_arr[i].product_type, 0);
    }

    tmp_arr = getOutputs(productionRecipe);
    for (int i = 0; i < factory->stockpiles_out_num; i++) {
        assignStockpileValues(&factory->stockpiles_out[i], tmp_arr[i].product_type, 0);
    }
}

inline QUANTITY_INT* getOrderedInQuantity(const Factory* factory, const Product product)
{
    for (int i = 0; i < factory->stockpiles_in_num; i++)
    {
        if (factory->stockpiles_in[i].product_type == product)
        {
            return &factory->ordered_in[i];
        }
    }
    return NULL;
}

inline QUANTITY_INT* getOrderedOutQuantity(const Factory* factory, const Product product)
{
    for (int i = 0; i < factory->stockpiles_out_num; i++)
    {
        if (factory->stockpiles_out[i].product_type == product)
        {
            return &factory->ordered_out[i];
        }
    }
    return NULL;
}

inline void addOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
    QUANTITY_INT* result = getOrderedInQuantity(factory, product);
    if (result != NULL)
    {
        if (QUANTITY_INT_MAX - quantity >= *result)
        {
            (*result) += quantity;
        }
    }
}

inline void addOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
    QUANTITY_INT* result = getOrderedOutQuantity(factory, product);
    if (result != NULL)
    {
        if (QUANTITY_INT_MAX - quantity >= *result)
        {
            (*result) += quantity;
        }
    }
}

inline void removeOrderedInQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
    QUANTITY_INT* result = getOrderedInQuantity(factory, product);
    if (result != NULL)
    {
        if (*result >= quantity)
        {
            (*result) -= quantity;
        }
    }
}

inline void removeOrderedOutQuantity(Factory* factory, const Product product, const QUANTITY_INT quantity)
{
    QUANTITY_INT* result = getOrderedOutQuantity(factory, product);
    if (result != NULL)
    {
        if (*result >= quantity)
        {
            (*result) -= quantity;
        }
    }
}

// TBU (CHECK FOR POSSIBLE, REVERT OTHERWISE)
inline void processTickFactory(Factory* factory)
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

    free(factory->ordered_in);
    free(factory->ordered_out);
}
