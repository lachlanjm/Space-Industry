#include "HistoryIterator.h"

HistoryIterator* newHistoryIterator(const void* data, const enum HistoryType history_type)
{
	HistoryIterator* iter = calloc(1, sizeof(HistoryIterator));
	if (iter == NULL) return NULL;

	iter->index = 0;
	iter->history_type = history_type;

	switch (history_type)
	{
		case HISTORY_ARRAY_TYPE:
			iter->data.hist_array = data;
			break;
		case HISTORY_ARRAY_AVG_TYPE:
			iter->data.hist_array_avg = data;
			break;
		case HISTORY_WTD_AVG_ARRAY_VALUE_TYPE:
		case HISTORY_WTD_AVG_ARRAY_WEIGHT_TYPE:
		case HISTORY_WTD_AVG_ARRAY_AVG_TYPE:
			iter->data.hist_wtd_avg_array = data;
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
			*value_buf = getValueAtIndexHistoryArray(iter->data.hist_array, iter->index++);
			break;
		case HISTORY_ARRAY_AVG_TYPE:
			if (iter->index == MAX_HISTORY) return 0;
			*value_buf = getValueAtIndexHistoryArrayAvg(iter->data.hist_array_avg, iter->index++);
			break;
		case HISTORY_WTD_AVG_ARRAY_VALUE_TYPE:
			if (iter->index == MAX_HISTORY) return 0;
			*value_buf = getValueAtIndexHistoryWtdAvgArray(iter->data.hist_wtd_avg_array, iter->index++);
			break;
		case HISTORY_WTD_AVG_ARRAY_WEIGHT_TYPE:
			if (iter->index == MAX_HISTORY) return 0;
			*value_buf = getWeightAtIndexHistoryWtdAvgArray(iter->data.hist_wtd_avg_array, iter->index++);
			break;
		case HISTORY_WTD_AVG_ARRAY_AVG_TYPE:
			if (iter->index == MAX_HISTORY) return 0;
			*value_buf = getAverageAtIndexHistoryWtdAvgArray(iter->data.hist_wtd_avg_array, iter->index++);
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
