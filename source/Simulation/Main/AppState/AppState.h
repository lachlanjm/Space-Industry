#ifndef APP_STATE_H
#define APP_STATE_H

typedef struct AppState AppState;

#include "..\..\Management\Logistics\LogisticsManager.h"
#include "..\..\Management\Production\FactoryManager.h"

#define SAVE_FILE_SEP "="
#define SAVE_FILE_PTR_PREFIX ">"
#define SAVE_FILE_ID_SEP "_"

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

	char* app_dir_path;
} AppState;

void processTickAppState(AppState* appState);

void cleanAppState(AppState* appState);

#endif