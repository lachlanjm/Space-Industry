#include "HistoryWtdAvgArray.h"

static HISTORY_ARRAY_ID_INT id_next = 0;

static int tick = 0;
static int index_base = 0;
HistoryWtdAvgArray* newHistoryWtdAvgArray()
{
	HistoryWtdAvgArray* hist_array = calloc(1, sizeof(HistoryWtdAvgArray));
	assignHistoryWtdAvgArrayValues(hist_array);
	return hist_array;
}

void assignHistoryWtdAvgArrayValues(HistoryWtdAvgArray* hist_array)
{
	// TODO this shouldn't actually be needed but it makes it work?
	for (int i=0;i<MAX_HISTORY;i++) { hist_array->values[i] = 0; }
	for (int i=0;i<MAX_HISTORY;i++) { hist_array->weights[i] = 0; }

	hist_array->sum_value = 0;
	hist_array->sum_weight = 0;
	hist_array->avg = 0;

	hist_array->id = id_next++;
}

void addToHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const HISTORY_INT value, const HISTORY_INT weight)
{
	hist_array->values[index_base] += value;
	hist_array->weights[index_base] += weight;
	hist_array->sum_value += value;
	hist_array->sum_weight += weight;
}

void subFromHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const HISTORY_INT value, const HISTORY_INT weight)
{
	hist_array->values[index_base] -= value;
	hist_array->weights[index_base] -= weight;
	hist_array->sum_value -= value;
	hist_array->sum_weight -= weight;
}

HISTORY_INT getValueAtIndexHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array, const int index)
{
	return hist_array->values[(index_base + index) % MAX_HISTORY];
}

void setValueAtIndexHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const int index, const HISTORY_INT value)
{
	hist_array->sum_value -= hist_array->values[(index_base + index) % MAX_HISTORY];
	hist_array->values[(index_base + index) % MAX_HISTORY] = value;
	hist_array->sum_value += value;
}

HISTORY_INT getWeightAtIndexHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array, const int index)
{
	return hist_array->weights[(index_base + index) % MAX_HISTORY];
}

void setWeightAtIndexHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const int index, const HISTORY_INT weight)
{
	hist_array->sum_weight -= hist_array->weights[(index_base + index) % MAX_HISTORY];
	hist_array->weights[(index_base + index) % MAX_HISTORY] = weight;
	hist_array->sum_weight += weight;
}

HISTORY_INT getSumValueHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array)
{
	return hist_array->sum_value;
}

HISTORY_INT getSumWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array)
{
	return hist_array->sum_weight;
}

HISTORY_INT getAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array)
{
	return hist_array->avg;
}

void tickHistoryWtdAvgArrayIndexStatic()
{
	index_base += ++tick / ITER_PER_HISTORY_TICK;
	tick %= ITER_PER_HISTORY_TICK;
	index_base %= MAX_HISTORY;
}

void tickHistoryWtdAvgArrayIndex(HistoryWtdAvgArray* hist_array)
{
	if (tick == 0)
	{
		// Just changed index_base forward
		hist_array->sum_value -= hist_array->values[index_base];
		hist_array->values[index_base] = 0;
		hist_array->sum_weight -= hist_array->weights[index_base];
		hist_array->weights[index_base] = 0;

		if (hist_array->sum_weight == 0) 
		{
			hist_array->avg = 0;
		}
		else
		{
			hist_array->avg = hist_array->sum_value / hist_array->sum_weight;
		}
	}
}

void cleanHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array)
{
	// NOTHING -> TBU
}
