#include "LoadAppState.h"

AppState* loadAppState(const int file_path_len, const char* file_path[])
{
    AppState* appState = (AppState*) malloc(sizeof(AppState));

    appState->factory_managers_num = 0;
    appState->factory_managers = (FactoryManager*) calloc(appState->factory_managers_num, sizeof(FactoryManager));

    for (int i = 0; i < appState->factory_managers_num; i++)
    {
        assignFactoryManagerValues(
            &appState->factory_managers[i],
            0, // TODO: TBU
            0
        );
    }

    appState->logistics_managers_num = 0;
    appState->logistics_managers_next_process_tick_index = 0;
    appState->logistics_managers = (LogisticsManager*) calloc(appState->logistics_managers_num, sizeof(LogisticsManager));

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        assignNewLogisticsManagerValues(
            &appState->logistics_managers[i],
            1 // TODO TBU
        );
    }

    return appState;
}
