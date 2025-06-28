#ifndef LOGISTICS_MANAGER_H
#define LOGISTICS_MANAGER_H

#include <stdint.h>

typedef struct LogisticsManager LogisticsManager;

#include "..\..\Transport\Structures\Vehicle.h"
#include "..\..\Environment\Enums\TransportNode.h"
#include "LogisticsContract.h"

#define LOGISTICS_MANAGER_ID_INT uint_least16_t

struct LogisticsManager 
{
	TransportNode headquarters_location;
	
	uint_fast16_t vehicles_num;
	Vehicle** vehicles;
	
	uint_fast16_t contracts_num;
	LogisticsContract* contracts;
	
	uint64_t wealth;
	
	LOGISTICS_MANAGER_ID_INT id;
};

#include "..\..\Environment\Structures\MarketMap.h"
#include "..\..\Population\Structures\Government.h"

#include <stdio.h>
#include <string.h>

#define LOGISTICS_MANAGER_NEW_VEHICLE_COST 100000
#define LOGISTICS_MANAGER_DESIRED_FREE_VEHICLE_FACTOR 0.1
#define LOGISTICS_MANAGER_MAX_WEALTH_DONATION_TRIGGER 2 // TODO remove after TBU

LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num, const TransportNode headquarters_location);
void assignLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num, const TransportNode headquarters_location);
void loadLogisticsManagerConstructorLogisticsContract(LogisticsManager* logisticsManager, const uint_fast16_t contracts_num);
void assignLoadIdLogisticsManager(LogisticsManager* obj, const int id);

void addVehicleToLogisticsManager(LogisticsManager* const logisticsManager);

void insertFundsLogisticsManager(LogisticsManager* logisticsManager, const int funds);
void withdrawFundsLogisticsManager(LogisticsManager* logisticsManager, const int funds);

void update_dist_to_profit_eff(void);

void processTickLogisticsManager(LogisticsManager* const logisticsManager);
void processTickLogisticsManagerContracts(LogisticsManager* const logisticsManager);
void processTickLogisticsManagerVehicles(const LogisticsManager* const logisticsManager);

void cleanLogisticsManager(LogisticsManager* logisticsManager);

#endif