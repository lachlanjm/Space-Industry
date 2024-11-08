#ifndef HISTORY_ARRAY_AVG_H
#define HISTORY_ARRAY_AVG_H

#include <stdlib.h>
#include <stdint.h>

#include "..\Helpers\HistoryStandards.h"

typedef struct HistoryArrayAvg {
	HISTORY_INT array[MAX_HISTORY];
	HISTORY_SUM_INT sum;
	HISTORY_INT avg;
	HISTORY_ARRAY_ID_INT id;
} HistoryArrayAvg;

HistoryArrayAvg* newHistoryArrayAvg();
void assignHistoryArrayAvgValues(HistoryArrayAvg* hist_array);
void assignLoadIdHistoryArrayAvg(HistoryArrayAvg* obj, const int id);

void addToHistoryArrayAvg(HistoryArrayAvg* hist_array, const HISTORY_INT value);
void subFromHistoryArrayAvg(HistoryArrayAvg* hist_array, const HISTORY_INT value);

HISTORY_INT getValueAtIndexHistoryArrayAvg(const HistoryArrayAvg* hist_array, const int index);
void setValueAtIndexHistoryArrayAvg(HistoryArrayAvg* hist_array, const int index, const HISTORY_INT value);

HISTORY_INT getMaxValueHistoryArrayAvg(const HistoryArrayAvg const* hist_array);
HISTORY_INT getMinValueHistoryArrayAvg(const HistoryArrayAvg const* hist_array);
HISTORY_SUM_INT getSumHistoryArrayAvg(const HistoryArrayAvg* hist_array);
HISTORY_INT getAvgHistoryArrayAvg(const HistoryArrayAvg* hist_array);

void tickHistoryArrayAvgIndexStatic();
void tickHistoryArrayAvgIndex(HistoryArrayAvg* hist_array);

void cleanHistoryArrayAvg(HistoryArrayAvg* hist_array);

#endif