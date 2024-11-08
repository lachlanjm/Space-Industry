#include "HistoryArray.h"

static HISTORY_ARRAY_ID_INT id_next = 0;

static int tick = 0;
static int index_base = 0;
HistoryArray* newHistoryArray()
{
	HistoryArray* hist_array = calloc(1, sizeof(HistoryArray));
	assignHistoryArrayValues(hist_array);
	return hist_array;
}

void assignHistoryArrayValues(HistoryArray* hist_array)
{
	// TODO this shouldn't actually be needed but it makes it work?
	for (int i=0;i<MAX_HISTORY;i++) { hist_array->array[i] = 0; }

	hist_array->id = id_next++;
}

void assignLoadIdHistoryArray(HistoryArray* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void addToHistoryArray(HistoryArray* hist_array, const HISTORY_INT value)
{
	hist_array->array[index_base] += value;
}

void subFromHistoryArray(HistoryArray* hist_array, const HISTORY_INT value)
{
	hist_array->array[index_base] -= value;
}

HISTORY_INT getValueAtIndexHistoryArray(const HistoryArray* hist_array, const int index)
{
	return hist_array->array[(index_base + index) % MAX_HISTORY];
}

void setValueAtIndexHistoryArray(HistoryArray* hist_array, const int index, const HISTORY_INT value)
{
	hist_array->array[(index_base + index) % MAX_HISTORY] = value;
}

void tickHistoryArrayIndexStatic()
{
	index_base += ++tick / ITER_PER_HISTORY_TICK;
	tick %= ITER_PER_HISTORY_TICK;
	index_base %= MAX_HISTORY;
}

void tickHistoryArrayIndex(HistoryArray* hist_array)
{
	if (tick == 0)
	{
		// Just changed index_base forward
		hist_array->array[index_base] = 0;
	}
}

void cleanHistoryArray(HistoryArray* hist_array)
{
	// NOTHING -> TBU
}
