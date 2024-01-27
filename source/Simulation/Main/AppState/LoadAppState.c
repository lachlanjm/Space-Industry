#include "LoadAppState.h"

AppState* loadAppState(const int file_path_len, const char* file_path)
{
    AppState* appState = (AppState*) malloc(sizeof(AppState));

    appState->factory_managers_num = PRODUCTION_RECIPE_COUNT;
    appState->factory_managers = (FactoryManager*) calloc(appState->factory_managers_num, sizeof(FactoryManager));

    for (int i = 0; i < appState->factory_managers_num; i++)
    {
        assignFactoryManagerValues(
            &appState->factory_managers[i],
            i, // TODO: TBU
            i
        );
    }

    appState->logistics_managers_num = 3;
    appState->logistics_managers_next_process_tick_index = 0;
    appState->logistics_managers = (LogisticsManager*) calloc(appState->logistics_managers_num, sizeof(LogisticsManager));

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        assignNewLogisticsManagerValues(
            &appState->logistics_managers[i],
            10 // TODO TBU
        );
    }

    for (int loc = 0; loc < TRANSPORT_NODE_COUNT; loc++)
    {
        for (int product = 0; product < PRODUCT_COUNT; product++)
        {
            getProductMarketAtLocation(loc, product)->highest_buy_order = NULL;
            getProductMarketAtLocation(loc, product)->lowest_sell_order = NULL;
        }
    }

    return appState;
}
