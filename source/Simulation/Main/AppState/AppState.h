#ifndef APP_STATE_H
#define APP_STATE_H

typedef struct AppState AppState;

#include "..\..\..\History\HistoryArray.h"
#include "..\..\..\History\HistoryArrayAvg.h"
#include "..\..\..\History\HistoryWtdAvgArray.h"

#include "..\..\Management\Logistics\LogisticsManager.h"
#include "..\..\Management\Production\Company.h"
#include "..\..\Population\Structures\LocalPopulation.h"
#include "..\..\Environment\Structures\MarketMap.h"

#include ".\LoadAppState.h"
#include ".\SaveAppState.h"

#include <stdint.h>
#include <stdio.h>

#define AS_LOG_MAN_GROUPS 4

typedef struct AppState {
	uint_fast16_t logistics_managers_num;
	uint_fast16_t logistics_managers_next_process_tick_index;
	LogisticsManager* logistics_managers;

	uint_fast16_t companies_num;
	Company* companies;
} AppState;

void processTickAppState(AppState* appState);
AppState* newGameAppState();

void cleanAppState(AppState* appState);

#endif