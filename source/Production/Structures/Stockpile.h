#ifndef STOCKPILE_H
#define STOCKPILE_H

#include "..\Enums\Product.h"

#include <stdint.h>
#include <stdlib.h>

#define QUANTITY_INT uint_fast32_t
#define QUANTITY_INT_MAX UINT_FAST32_MAX

typedef struct Stockpile
{
    Product product_type;
    QUANTITY_INT quantity;
} Stockpile;

Stockpile* newStockpile(const Product product, const QUANTITY_INT quantity);
inline void assignStockpileValues(Stockpile* stockpile, const Product product, const QUANTITY_INT quantity);
inline void setDiffProduct(Stockpile* stockpile, const Product product);
inline void addQuantity(Stockpile* stockpile, const QUANTITY_INT quantity);
inline uint_fast8_t addQuantityCheck(Stockpile* stockpile, const QUANTITY_INT quantity);
inline void removeQuantity(Stockpile* stockpile, const QUANTITY_INT quantity);
inline uint_fast8_t removeQuantityCheck(Stockpile* stockpile, const QUANTITY_INT quantity);
inline uint_fast8_t moveStockpile(Stockpile* stockpile_out, Stockpile* stockpile_in, const QUANTITY_INT quantity);

// DO NOT CLEAN ITEM (ONLY CONSTITUENTS)
void cleanStockpile(Stockpile* stockpile);

#endif