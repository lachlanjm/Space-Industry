#ifndef LOGISTICS_MANAGER_H
#define LOGISTICS_MANAGER_H

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

void cleanLogisticsManager(LogisticsManager* logisticsManager);

#endif