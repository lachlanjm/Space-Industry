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
	for (int i=0;i<MAX_HISTORY;i++) 
	{ 
		hist_array->values[i] = 0; 
		hist_array->weights[i] = 0;
		hist_array->averages[i] = 0;
	}

	hist_array->sum_value = 0;
	hist_array->sum_weight = 0;

	hist_array->id = id_next++;
}

void assignLoadIdHistoryWtdAvgArray(HistoryWtdAvgArray* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
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

HISTORY_INT getAverageAtIndexHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array, const int index)
{
	return hist_array->averages[(index_base + index) % MAX_HISTORY];
}

void setAverageAtIndexHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const int index, const HISTORY_INT average)
{
	hist_array->averages[(index_base + index) % MAX_HISTORY] = average;
}

HISTORY_INT getMaxValueHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array)
{
	HISTORY_INT result = hist_array->values[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result < hist_array->values[i]) result = hist_array->values[i];
	return result;
}
HISTORY_INT getMaxWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array)
{
	HISTORY_INT result = hist_array->weights[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result < hist_array->weights[i]) result = hist_array->weights[i];
	return result;
}
HISTORY_INT getMaxAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array)
{
	HISTORY_INT result = hist_array->averages[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result < hist_array->averages[i]) result = hist_array->averages[i];
	return result;
}
HISTORY_INT getMinValueHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array)
{
	HISTORY_INT result = hist_array->values[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result > hist_array->values[i]) result = hist_array->values[i];
	return result;
}
HISTORY_INT getMinWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array)
{
	HISTORY_INT result = hist_array->weights[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result > hist_array->weights[i]) result = hist_array->weights[i];
	return result;
}
HISTORY_INT getMinAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array)
{
	HISTORY_INT result = hist_array->averages[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result > hist_array->averages[i]) result = hist_array->averages[i];
	return result;
}

HISTORY_FLOAT getSumValueHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array)
{
	return hist_array->sum_value;
}

HISTORY_FLOAT getSumWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array)
{
	return hist_array->sum_weight;
}

HISTORY_INT getAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array)
{
	return hist_array->averages[index_base];
}

void tickHistoryWtdAvgArrayIndexStatic()
{
	index_base += ++tick / ITER_PER_HISTORY_TICK;
	tick %= ITER_PER_HISTORY_TICK;
	index_base %= MAX_HISTORY;
}

static inline void recalcHistoryArraySums(HistoryWtdAvgArray* const hist_array)
{
	hist_array->sum_value = 0;
	hist_array->sum_weight = 0;
	hist_array->values[index_base] = 0;
	hist_array->weights[index_base] = 0;
	for (int i = 0; i < MAX_HISTORY; i++)
	{
		hist_array->sum_value += hist_array->values[i];
		hist_array->sum_weight += hist_array->weights[i];
	}
}

void tickHistoryWtdAvgArrayIndex(HistoryWtdAvgArray* hist_array)
{
	if (tick == 0)
	{
		// Just changed index_base forward
		if (
			ABS(hist_array->values[index_base]) >= ABS(hist_array->sum_value) / HISTORY_FLOAT_RECALC_FACTOR
			|| ABS(hist_array->weights[index_base]) >= ABS(hist_array->sum_weight) / HISTORY_FLOAT_RECALC_FACTOR
		)
		{
			recalcHistoryArraySums(hist_array);
		}
		else
		{
			hist_array->sum_value -= hist_array->values[index_base];
			hist_array->values[index_base] = 0;
			hist_array->sum_weight -= hist_array->weights[index_base];
			hist_array->weights[index_base] = 0;
		}

		if (hist_array->sum_weight == 0) 
		{
			hist_array->averages[index_base] = 0;
		}
		else
		{
			hist_array->averages[index_base] = hist_array->sum_value / hist_array->sum_weight;
		}
	}
}

void cleanHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array)
{
	// NOTHING -> TBU
	// UPDATE GOV clean if so
}
