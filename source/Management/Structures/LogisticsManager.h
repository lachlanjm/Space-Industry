#ifndef LOGISTICS_MANAGER_H
#define LOGISTICS_MANAGER_H

#include "..\..\Environment\Structures\MarketMap.h"
#include "..\..\Transport\Structures\Vehicle.h"
#include "LogisticsContract.h"

#include <stdint.h>

typedef struct LogisticsManager 
{
    uint_fast16_t vehicles_num;
    Vehicle* vehicles;

    uint_fast16_t contracts_num;
    LogisticsContract* contracts;

} LogisticsManager;

inline LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num);
inline void assignNewLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num);

void update_dist_to_price_eff();

void processTickLogisticsManagerContracts(LogisticsManager* logisticsManager);
void processTickLogisticsManagerVehicles(LogisticsManager* logisticsManager);

void cleanLogisticsManager(LogisticsManager* logisticsManager);

#endif