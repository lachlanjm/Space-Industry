#ifndef LOGISTICS_MANAGER_H
#define LOGISTICS_MANAGER_H

typedef struct LogisticsManager LogisticsManager;

#include "..\..\Transport\Structures\Vehicle.h"
#include "LogisticsContract.h"

#include <stdint.h>

#define LOGISTICS_MANAGER_ID_INT uint_least16_t

struct LogisticsManager 
{
	uint_fast16_t vehicles_num;
	Vehicle* vehicles;

	uint_fast16_t contracts_num;
	LogisticsContract* contracts;

	int wealth;

	LOGISTICS_MANAGER_ID_INT id;
};

#include "..\..\Environment\Structures\MarketMap.h"

#include <stdio.h>

LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num);
void assignLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num);
void loadLogisticsManagerConstructorVehicles(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num);
void loadLogisticsManagerConstructorLogisticsContract(LogisticsManager* logisticsManager, const uint_fast16_t contracts_num);
void assignLoadIdLogisticsManager(LogisticsManager* obj, const int id);

void insertFundsLogisticsManager(LogisticsManager* logisticsManager, const int funds);
void withdrawFundsLogisticsManager(LogisticsManager* logisticsManager, const int funds);

void update_dist_to_price_eff(void);

void processTickLogisticsManager(LogisticsManager* logisticsManager);
void processTickLogisticsManagerContracts(LogisticsManager* logisticsManager);
void processTickLogisticsManagerVehicles(LogisticsManager* logisticsManager);

void cleanLogisticsManager(LogisticsManager* logisticsManager);

#endif