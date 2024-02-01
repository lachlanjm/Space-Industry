#ifndef APP_STATE_H
#define APP_STATE_H

typedef struct AppState AppState;

#include "..\..\Management\Logistics\LogisticsManager.h"
#include "..\..\Management\Production\FactoryManager.h"


#include ".\LoadAppState.h"
#include ".\SaveAppState.h"

#include <stdint.h>
#include <stdio.h>

typedef struct AppState {
	uint_fast16_t logistics_managers_num;
	uint_fast16_t logistics_managers_next_process_tick_index;
	LogisticsManager* logistics_managers;

	uint_fast16_t factory_managers_num;
	FactoryManager* factory_managers;
} AppState;

void processTickAppState(AppState* appState);

void cleanAppState(AppState* appState);

#endif