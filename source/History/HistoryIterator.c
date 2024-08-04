#include "HistoryIterator.h"

HistoryIterator* newHistoryIterator(const void* data, const enum HistoryType history_type)
{
	HistoryIterator* iter = malloc(sizeof(HistoryIterator));
	if (iter == NULL) return NULL;

	iter->index = 0;
	iter->history_type = history_type;

	switch (history_type)
	{
		case HISTORY_ARRAY_TYPE:
			iter->data.hist_array = data;
			break;
		default:
			free(iter);
			return NULL;
	}

	return iter;
}

int getNextHistoryIterItem(HistoryIterator* iter, HISTORY_INT* value_buf)
{
	switch (iter->history_type)
	{
		case HISTORY_ARRAY_TYPE:
			if (iter->index == MAX_HISTORY) return 0;
			*value_buf = getValueAtIndex(iter->data.hist_array, iter->index++);
			break;
		default:
			return 0;
	}
	return 1;
}

int closeHistoryIterator(HistoryIterator* iter)
{
	free(iter);
	return 0;
}
