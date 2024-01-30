#ifndef LOGISTICS_MANAGER_H
#define LOGISTICS_MANAGER_H

#include "..\..\Environment\Structures\MarketMap.h"
#include "..\..\Transport\Structures\Vehicle.h"
#include "LogisticsContract.h"

#include <stdint.h>

#define LOGISTICS_MANAGER_ID_INT uint_least16_t

typedef struct LogisticsManager 
{
	uint_fast16_t vehicles_num;
	Vehicle* vehicles;

	uint_fast16_t contracts_num;
	LogisticsContract* contracts;

	LOGISTICS_MANAGER_ID_INT id;
} LogisticsManager;

LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num);
void assignNewLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num);
void assignFreeVehicles(LogisticsManager* logisticsManager);
void assignNewLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle);
void loadLogisticsManagerConstructorVehicles(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num);
void loadLogisticsManagerConstructorLogisticsContract(LogisticsManager* logisticsManager, const uint_fast16_t contracts_num);

void update_dist_to_price_eff();

void processTickLogisticsManagerContracts(LogisticsManager* logisticsManager);
void processTickLogisticsManagerVehicles(LogisticsManager* logisticsManager);

void cleanLogisticsManager(LogisticsManager* logisticsManager);

#endif