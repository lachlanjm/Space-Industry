#include "HistoryArray.h"

static int tick = 0;
static int index_base = 0;
HistoryArray* newHistoryArray()
{
	HistoryArray* hist_array = calloc(1, sizeof(HistoryArray));
	assignNewHistoryArrayValues(hist_array);
	return hist_array;
}

void assignNewHistoryArrayValues(HistoryArray* hist_array)
{
	// NOTHING -> TBU
}

void addToHistoryArray(HistoryArray* hist_array, const HISTORY_INT value)
{
	hist_array->array[index_base] += value;
}

void subFromHistoryArray(HistoryArray* hist_array, const HISTORY_INT value)
{
	hist_array->array[index_base] -= value;
}

HISTORY_INT getValueAtIndex(const HistoryArray* hist_array, const int index)
{
	return hist_array->array[(index_base + index) % MAX_HISTORY];
}

void tickHistoryArrayIndexStatic()
{
	index_base += ++tick / ITER_PER_HISTORY_TICK;
	tick %= ITER_PER_HISTORY_TICK;
	index_base %= MAX_HISTORY;
}

void tickHistoryArrayIndexClean(HistoryArray* hist_array)
{
	hist_array->array[index_base] = 0;
}

void cleanHistoryArray(HistoryArray* hist_array)
{
	// NOTHING -> TBU
}
