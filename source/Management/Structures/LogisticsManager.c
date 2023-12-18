#include "LogisticsManager.h"

inline LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num)
{
    LogisticsManager* logisticsManager = (LogisticsManager*) malloc(1 * sizeof(LogisticsManager));
    assignNewLogisticsManagerValues(logisticsManager, vehicles_num);
    return logisticsManager;
}

inline void assignNewLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num)
{
    logisticsManager->vehicles_num = vehicles_num;

    logisticsManager->vehicles = (Vehicle*) realloc(logisticsManager->vehicles, vehicles_num * sizeof(Vehicle));

    logisticsManager->contracts_num = 0;
    logisticsManager->contracts = NULL;
}

void cleanLogisticsManager(LogisticsManager* logisticsManager)
{
    for (int i = 0; i < logisticsManager->vehicles_num; i++)
    {
        cleanVehicle(&logisticsManager->vehicles[i]);
    }
    free(logisticsManager->vehicles);

    for (int i = 0; i < logisticsManager->contracts_num; i++)
    {
        cleanContract(&logisticsManager->contracts[i]);
    }
    // free(logisticsManager->contracts); TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

