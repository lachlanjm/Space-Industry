#include "AppState.h"

void processTickAppState(AppState* appState)
{
	tickHistoryArrayIndexStatic();
	tickHistoryArrayAvgIndexStatic();
	tickHistoryWtdAvgArrayIndexStatic();
	processTickFactoryStatic();

	processTickMarketMap();

	// MUST DO FACTORY BEFORE LOGISTICS (HISTORY SAVING FLOW)
	for (int i = 0; i < appState->companies_num; i++)
	{
		processTickCompany(&appState->companies[i]);
	}

	update_dist_to_price_eff();
	for (int i = 0; i < appState->logistics_managers_num; i++)
	{
		if (i % AS_LOG_MAN_GROUPS == appState->logistics_managers_next_process_tick_index)
		{
			processTickLogisticsManagerContracts(&appState->logistics_managers[i]);
			processTickLogisticsManager(&appState->logistics_managers[i]); // TODO MOVE
		}
		processTickLogisticsManagerVehicles(&appState->logistics_managers[i]);
	}
	appState->logistics_managers_next_process_tick_index++;
	appState->logistics_managers_next_process_tick_index %= AS_LOG_MAN_GROUPS;

	for (int i = 0; i < getLocalPopulationNum(); i++)
	{
		processTickLocalPopulation(getLocalPopulationByLocation(i));
	}

	for (int i = 0; i < appState->government_num; i++)
	{
		processTickGovernment(&appState->governments[i]);
	}
}

AppState* newGameAppState()
{
	AppState* appState = calloc(1, sizeof(AppState));
	if (appState == NULL) return NULL;

	appState->companies_num = 3 * (PRODUCTION_RECIPE_COUNT - 1);
    appState->logistics_managers_num = PRODUCTION_RECIPE_COUNT;
	appState->government_num = 2;

    appState->companies = (Company*) calloc(appState->companies_num, sizeof(Company));
    for (int i = 0; i < appState->companies_num; i++) // LEAVE POP CONSUMPTION
    {
        assignCompanyValues(
            &appState->companies[i],
            i % (PRODUCTION_RECIPE_COUNT - 1),
            i % (TRANSPORT_NODE_COUNT)
        );
    }

    appState->logistics_managers_next_process_tick_index = 0;
    appState->logistics_managers = (LogisticsManager*) calloc(appState->logistics_managers_num, sizeof(LogisticsManager));

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        assignLogisticsManagerValues(
            &appState->logistics_managers[i],
            10,
			i%TRANSPORT_NODE_COUNT
        );
    }

	setTransportNodeCountLocalPopulationStatic(TRANSPORT_NODE_COUNT);
	for (int i = 0; i < getLocalPopulationNum(); i++)
	{
		assignLocalPopulationValues(i, 1000);
	}

	setGovernmentControlStatic(TRANSPORT_NODE_COUNT);
	appState->governments = (Government*) calloc(appState->government_num, sizeof(Government));
	
	for (int i = 0; i < appState->government_num; i++)
	{
		assignGovernmentValues(&appState->governments[i], 3000);
	}
	for (int i = 0; i < TRANSPORT_NODE_COUNT; i++)
	{
		setGovernmentControlByLocation(&appState->governments[i%appState->government_num], i);
	}

	instantiateNewMarketMap(TRANSPORT_NODE_COUNT, PRODUCT_COUNT);

	return appState;
}

void cleanAppState(AppState* appState)
{
	for (int i = 0; i < appState->companies_num; i++)
	{
		cleanCompany(&appState->companies[i]);
	}
	free(appState->companies);

	for (int i = 0; i < appState->logistics_managers_num; i++)
	{
		cleanLogisticsManager(&appState->logistics_managers[i]);
	}
	free(appState->logistics_managers);

	for (int i = 0; i < appState->government_num; i++)
	{
		cleanGovernment(&appState->governments[i]);
	}
	free(appState->governments);

	cleanTransportNodeCountLocalPopulationStatic();
	cleanGovernmentControlStatic();
	cleanMarketMap();
}