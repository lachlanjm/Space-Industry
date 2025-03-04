#include "HistoryArrayAvg.h"

static HISTORY_ARRAY_ID_INT id_next = 0;

static int tick = 0;
static int index_base = 0;
HistoryArrayAvg* newHistoryArrayAvg()
{
	HistoryArrayAvg* hist_array = calloc(1, sizeof(HistoryArrayAvg));
	assignHistoryArrayAvgValues(hist_array);
	return hist_array;
}

void assignHistoryArrayAvgValues(HistoryArrayAvg* hist_array)
{
	// TODO this shouldn't actually be needed but it makes it work?
	for (int i=0;i<MAX_HISTORY;i++) { hist_array->array[i] = 0; }

	hist_array->sum = 0;
	hist_array->avg = 0;

	hist_array->id = id_next++;
}

void assignLoadIdHistoryArrayAvg(HistoryArrayAvg* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void addToHistoryArrayAvg(HistoryArrayAvg* hist_array, const HISTORY_INT value)
{
	hist_array->array[index_base] += value;
	hist_array->sum += value;
}

void subFromHistoryArrayAvg(HistoryArrayAvg* hist_array, const HISTORY_INT value)
{
	hist_array->array[index_base] -= value;
	hist_array->sum -= value;
}

HISTORY_INT getValueAtIndexHistoryArrayAvg(const HistoryArrayAvg* hist_array, const int index)
{
	return hist_array->array[(index_base + index) % MAX_HISTORY];
}

void setValueAtIndexHistoryArrayAvg(HistoryArrayAvg* hist_array, const int index, const HISTORY_INT value)
{
	hist_array->sum -= hist_array->array[(index_base + index) % MAX_HISTORY];
	hist_array->array[(index_base + index) % MAX_HISTORY] = value;
	hist_array->sum += value;
	hist_array->avg = hist_array->sum / MAX_HISTORY;
}

HISTORY_INT getMaxValueHistoryArrayAvg(const HistoryArrayAvg* const hist_array)
{
	HISTORY_INT result = hist_array->array[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result < hist_array->array[i]) result = hist_array->array[i];
	return result;
}
HISTORY_INT getMinValueHistoryArrayAvg(const HistoryArrayAvg* const hist_array)
{
	HISTORY_INT result = hist_array->array[0];
	for (int i=1;i<MAX_HISTORY;i++) if (result > hist_array->array[i]) result = hist_array->array[i];
	return result;
}

HISTORY_FLOAT getSumHistoryArrayAvg(const HistoryArrayAvg* hist_array)
{
	return hist_array->sum;
}

HISTORY_FLOAT getAvgHistoryArrayAvg(const HistoryArrayAvg* hist_array)
{
	return hist_array->avg;
}

void tickHistoryArrayAvgIndexStatic()
{
	index_base += ++tick / ITER_PER_HISTORY_TICK;
	tick %= ITER_PER_HISTORY_TICK;
	index_base %= MAX_HISTORY;
}

static inline void recalcHistoryArraySum(HistoryArrayAvg* const hist_array)
{
	hist_array->sum = 0;
	hist_array->array[index_base] = 0;
	for (int i = 0; i < MAX_HISTORY; i++) hist_array->sum += hist_array->array[i];
}

void tickHistoryArrayAvgIndex(HistoryArrayAvg* hist_array)
{
	if (tick == 0)
	{
		// Just changed index_base forward
		if (ABS(hist_array->array[index_base]) >= ABS(hist_array->sum) / HISTORY_FLOAT_RECALC_FACTOR)
		{
			recalcHistoryArraySum(hist_array);
		}
		else
		{
			hist_array->sum -= hist_array->array[index_base];
			hist_array->array[index_base] = 0;
		}
		hist_array->avg = hist_array->sum / MAX_HISTORY;
	}
}

void cleanHistoryArrayAvg(HistoryArrayAvg* hist_array)
{
	// NOTHING -> TBU
}
