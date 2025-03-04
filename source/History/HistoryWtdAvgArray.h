#ifndef HISTORY_WTD_AVG_ARRAY_H
#define HISTORY_WTD_AVG_ARRAY_H

#include <stdlib.h>
#include <stdint.h>

#include "..\Helpers\HistoryStandards.h"

typedef struct HistoryWtdAvgArray {
	HISTORY_INT values[MAX_HISTORY];
	HISTORY_INT weights[MAX_HISTORY];
	HISTORY_INT averages[MAX_HISTORY];
	HISTORY_FLOAT sum_value;
	HISTORY_FLOAT sum_weight;
	HISTORY_ARRAY_ID_INT id;
} HistoryWtdAvgArray;

HistoryWtdAvgArray* newHistoryWtdAvgArray();
void assignHistoryWtdAvgArrayValues(HistoryWtdAvgArray* hist_array);
void assignLoadIdHistoryWtdAvgArray(HistoryWtdAvgArray* obj, const int id);

void addToHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const HISTORY_INT value, const HISTORY_INT weight);
void subFromHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const HISTORY_INT value, const HISTORY_INT weight);

HISTORY_INT getValueAtIndexHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array, const int index);
void setValueAtIndexHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const int index, const HISTORY_INT value);

HISTORY_INT getWeightAtIndexHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array, const int index);
void setWeightAtIndexHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const int index, const HISTORY_INT weight);

HISTORY_INT getAverageAtIndexHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array, const int index);
void setAverageAtIndexHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array, const int index, const HISTORY_INT average);

HISTORY_INT getMaxValueHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array);
HISTORY_INT getMaxWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array);
HISTORY_INT getMaxAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array);
HISTORY_INT getMinValueHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array);
HISTORY_INT getMinWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array);
HISTORY_INT getMinAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* const hist_array);

HISTORY_FLOAT getSumValueHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array);
HISTORY_FLOAT getSumWeightHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array);
HISTORY_INT getAvgHistoryWtdAvgArray(const HistoryWtdAvgArray* hist_array);

void tickHistoryWtdAvgArrayIndexStatic();
void tickHistoryWtdAvgArrayIndex(HistoryWtdAvgArray* hist_array);

void cleanHistoryWtdAvgArray(HistoryWtdAvgArray* hist_array);

#endif