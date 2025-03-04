#include "Stockpile.h"

static STOCKPILE_ID_INT id_next = 0;

/* Avoid use, batch allocating is better */
Stockpile* newStockpile(const Product product, const QUANTITY_INT quantity) {
	Stockpile* stockpile = (Stockpile*) calloc(1, sizeof(Stockpile));
	assignStockpileValues(stockpile, product, quantity);
	return stockpile;
}

void assignStockpileValues(Stockpile* stockpile, const Product product, const QUANTITY_INT quantity) {
	stockpile->product_type = product;
	stockpile->quantity = quantity;

	assignHistoryArrayValues(&stockpile->quantity_history);

	stockpile->id = id_next++;
}

void assignLoadIdStockpile(Stockpile* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void setDiffProduct(Stockpile* stockpile, const Product product)
{
	if (stockpile->quantity == 0) {
		stockpile->product_type = product;
	}
}

void addQuantity(Stockpile* stockpile, const QUANTITY_INT quantity) {
	if (QUANTITY_INT_MAX - stockpile->quantity >= quantity) {
		stockpile->quantity += quantity;
		addToHistoryArray(&stockpile->quantity_history, quantity);
	}
}

uint_fast8_t addQuantityCheck(Stockpile* stockpile, const QUANTITY_INT quantity) {
	if (QUANTITY_INT_MAX - stockpile->quantity >= quantity) {
		stockpile->quantity += quantity;
		addToHistoryArray(&stockpile->quantity_history, quantity);
		return 0;
	}
	return 1;
}

void removeQuantity(Stockpile* stockpile, const QUANTITY_INT quantity) {
	if (stockpile->quantity >= quantity) {
		stockpile->quantity -= quantity;
		subFromHistoryArray(&stockpile->quantity_history, quantity);
	}
}

uint_fast8_t removeQuantityCheck(Stockpile* stockpile, const QUANTITY_INT quantity) {
	if (stockpile->quantity >= quantity) {
		stockpile->quantity -= quantity;
		subFromHistoryArray(&stockpile->quantity_history, quantity);
		return 0;
	}
	return 1;
}

uint_fast8_t moveStockpile(Stockpile* stockpile_out, Stockpile* stockpile_in, const QUANTITY_INT quantity) {
	if (stockpile_out->product_type != stockpile_in->product_type) {
		return 1;
	}
	switch (removeQuantityCheck(stockpile_out, quantity) + addQuantityCheck(stockpile_in, quantity)*2)
	{
	case 0:
		return 0;
	case 1:
		removeQuantity(stockpile_in, quantity);
		return 1;
	case 2:
		addQuantity(stockpile_out, quantity);
		return 1;
	default:
		return 1;
	}
}

void processTickStockpile(Stockpile* stockpile)
{
	tickHistoryArrayIndex(&stockpile->quantity_history);
}

void cleanStockpile(Stockpile* stockpile)
{
	cleanHistoryArray(&stockpile->quantity_history);
}
