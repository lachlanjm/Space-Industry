#ifndef APP_STATE_H
#define APP_STATE_H

#include ".\LoadAppState.h"
#include ".\SaveAppState.h"

#include "..\Management\Logistics\LogisticsManager.h"
#include "..\Management\Production\FactoryManager.h"

#include <stdint.h>

#define NUMBER_OF_ITERATIONS 100 // TEMPORARY: TBU

typedef struct AppState {
    uint_fast16_t logistics_managers_num;
    uint_fast16_t logistics_managers_next_process_tick_index;
    LogisticsManager* logistics_managers;

    uint_fast16_t factory_managers_num;
    FactoryManager* factory_managers;

} AppState;

int main(int argc, char* argv[]);

void processTickAppState(AppState* appState);

void cleanAppState(AppState* appState);

#endif