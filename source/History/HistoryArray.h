#ifndef HISTORY_ARRAY_H
#define HISTORY_ARRAY_H

#include <stdlib.h>
#include <stdint.h>

#include "..\Helpers\HistoryStandards.h"

typedef struct HistoryArray {
	HISTORY_INT array[MAX_HISTORY];
	HISTORY_ARRAY_ID_INT id;
} HistoryArray;

HistoryArray* newHistoryArray();
void assignHistoryArrayValues(HistoryArray* hist_array);

void addToHistoryArray(HistoryArray* hist_array, const HISTORY_INT value);
void subFromHistoryArray(HistoryArray* hist_array, const HISTORY_INT value);

HISTORY_INT getValueAtIndexHistoryArray(const HistoryArray* hist_array, const int index);
void setValueAtIndexHistoryArray(HistoryArray* hist_array, const int index, const HISTORY_INT value);

void tickHistoryArrayIndexStatic();
void tickHistoryArrayIndex(HistoryArray* hist_array);

void cleanHistoryArray(HistoryArray* hist_array);

#endif