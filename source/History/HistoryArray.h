#ifndef HISTORY_ARRAY_H
#define HISTORY_ARRAY_H

#include <stdlib.h>
#include <stdint.h>

#include "..\Helpers\HistoryStandards.h"

typedef struct HistoryArray {
	HISTORY_INT array[MAX_HISTORY];
} HistoryArray;

HistoryArray* newHistoryArray();
void assignNewHistoryArrayValues(HistoryArray* hist_array);

void addToHistoryArray(HistoryArray* hist_array, const HISTORY_INT value);
void subFromHistoryArray(HistoryArray* hist_array, const HISTORY_INT value);

HISTORY_INT getValueAtIndex(const HistoryArray* hist_array, const int index);

void tickHistoryArrayIndexStatic();
void tickHistoryArrayIndexClean(HistoryArray* hist_array);

void cleanHistoryArray(HistoryArray* hist_array);

#endif