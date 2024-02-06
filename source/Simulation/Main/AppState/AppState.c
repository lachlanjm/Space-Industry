#include "AppState.h"

void processTickAppState(AppState* appState)
{
	for (int i = 0; i < appState->factory_managers_num; i++)
	{
		processTickFactoryManager(&appState->factory_managers[i]);
	}

	update_dist_to_price_eff();
	for (int i = 0; i < appState->logistics_managers_num; i++)
	{
		if (i % AS_LOG_MAN_GROUPS == appState->logistics_managers_next_process_tick_index)
		{
			processTickLogisticsManagerContracts(&appState->logistics_managers[i]);
		}
		processTickLogisticsManagerVehicles(&appState->logistics_managers[i]);
	}
	appState->logistics_managers_next_process_tick_index++;
	appState->logistics_managers_next_process_tick_index %= AS_LOG_MAN_GROUPS;

	for (int i = 0; i < appState->local_population_num; i++)
	{
		processTickLocalPopulation(&appState->local_population[i]);
	}
}

AppState* newGameAppState()
{
	AppState* appState = calloc(1, sizeof(AppState));
	if (appState == NULL) return NULL;

	appState->factory_managers_num = 3 * (PRODUCTION_RECIPE_COUNT - 1);
    appState->factory_managers = (FactoryManager*) calloc(appState->factory_managers_num, sizeof(FactoryManager));

    for (int i = 0; i < appState->factory_managers_num; i++) // LEAVE POP CONSUMPTION
    {
        assignFactoryManagerValues(
            &appState->factory_managers[i],
            i % (PRODUCTION_RECIPE_COUNT - 1),
            i % (TRANSPORT_NODE_COUNT)
        );
    }

    appState->logistics_managers_num = PRODUCTION_RECIPE_COUNT;
    appState->logistics_managers_next_process_tick_index = 0;
    appState->logistics_managers = (LogisticsManager*) calloc(appState->logistics_managers_num, sizeof(LogisticsManager));

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        assignNewLogisticsManagerValues(
            &appState->logistics_managers[i],
            10
        );
    }

	appState->local_population_num = TRANSPORT_NODE_COUNT;
    appState->local_population = (LocalPopulation*) calloc(appState->local_population_num, sizeof(LocalPopulation));
	for (int i = 0; i < appState->local_population_num; i++)
	{
		assignLocalPopulationValues(
            &appState->local_population[i],
			i,
			1000 // TODO TBU
		);
	}

	return appState;
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

	for (int i = 0; i < appState->local_population_num; i++)
	{
		cleanLocalPopulation(&appState->local_population[i]);
	}
	free(appState->local_population);
}