#ifndef STOCKPILE_H
#define STOCKPILE_H

#include "..\..\..\History\HistoryArray.h"
#include "..\Enums\Product.h"

#include <stdint.h>
#include <stdlib.h>

#define STOCKPILE_ID_INT uint_least16_t

#define QUANTITY_INT uint_fast32_t
#define QUANTITY_INT_MAX UINT_FAST32_MAX

typedef struct Stockpile
{
	Product product_type;
	QUANTITY_INT quantity;

	HistoryArray quantity_history;
	STOCKPILE_ID_INT id;
} Stockpile;

Stockpile* newStockpile(const Product product, const QUANTITY_INT quantity);
void assignStockpileValues(Stockpile* stockpile, const Product product, const QUANTITY_INT quantity);
void assignLoadIdStockpile(Stockpile* obj, const int id);

void setDiffProduct(Stockpile* stockpile, const Product product);
void addQuantity(Stockpile* stockpile, const QUANTITY_INT quantity);
uint_fast8_t addQuantityCheck(Stockpile* stockpile, const QUANTITY_INT quantity);
void removeQuantity(Stockpile* stockpile, const QUANTITY_INT quantity);
uint_fast8_t removeQuantityCheck(Stockpile* stockpile, const QUANTITY_INT quantity);
uint_fast8_t moveStockpile(Stockpile* stockpile_out, Stockpile* stockpile_in, const QUANTITY_INT quantity);

void processTickStockpile(Stockpile* stockpile);

// DO NOT CLEAN ITEM (ONLY CONSTITUENTS)
void cleanStockpile(Stockpile* stockpile);

#endif