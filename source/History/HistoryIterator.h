#ifndef HISTORY_ITERATOR_H
#define HISTORY_ITERATOR_H

#include "..\Helpers\HistoryStandards.h"
#include "HistoryArray.h"

enum HistoryType {
	HISTORY_ARRAY_TYPE
};

typedef struct HistoryIterator {
	enum HistoryType history_type;
	int index;
	union
	{
		HistoryArray* hist_array;
	} data;
	
} HistoryIterator;

HistoryIterator* newHistoryIterator(const void* data, const enum HistoryType history_type);

// Returns 0 on error, 1 on success
int getNextHistoryIterItem(HistoryIterator* iter, HISTORY_INT* value_buf);

// Returns non-0 on error, 0 on success
int closeHistoryIterator(HistoryIterator* iter);

#endif