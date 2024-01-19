#include "AppState.h"

int main(int argc, char* argv[])
{
    AppState* current_app_state = loadAppState(0, NULL);

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
        printf("Iteration - %d\n", i);
        processTickAppState(current_app_state);
    }

    printf("Completed Iterations\n");

    saveAppState(current_app_state);
    cleanAppState(current_app_state);
    free(current_app_state);
}

void processTickAppState(AppState* appState)
{
    for (int i = 0; i < appState->factory_managers_num; i++)
    {
        printf("\tFM - %d\n", i);
        processTickFactoryManager(&appState->factory_managers[i]);
    }
    printf("\tCompleted FMs\n");

    processTickLogisticsManagerContracts(&appState->logistics_managers[appState->logistics_managers_next_process_tick_index]);
    appState->logistics_managers_next_process_tick_index = (++appState->logistics_managers_next_process_tick_index) % appState->logistics_managers_num;
    printf("\tCompleted Contract Phase\n");

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        printf("\tLM - %d\n", i);
        processTickLogisticsManagerVehicles(&appState->logistics_managers[i]);
    }
    printf("\tCompleted LMs\n");
}

void cleanAppState(AppState* appState)
{
    for (int i = 0; i < appState->factory_managers_num; i++)
    {
        cleanFactoryManager(&appState->factory_managers[i]);
    }
    free(appState->factory_managers);

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        cleanLogisticsManager(&appState->logistics_managers[i]);
    }
    free(appState->logistics_managers);
}
