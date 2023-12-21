#ifndef LOGISTICS_CONTRACT_H
#define LOGISTICS_CONTRACT_H

#include "..\..\Transport\Structures\Vehicle.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\..\Production\Enums\Product.h"

enum ContractPhase {
    ASSIGNMENT,
    PICK_UP,
    DELIVERY,
    COMPLETED
};

typedef struct LogisticsContract 
{
    // uint_fast16_t vehicle_num;
    Vehicle* assigned_vehicle; // TODO make array

    Factory* selling_factory;
    Factory* buying_factory;

    enum ContractPhase current_phase;
    Product product;
    QUANTITY_INT quantity;
} LogisticsContract;

LogisticsContract* newLogisticsContract(const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity);
void assignNewLogisticsContractValues(LogisticsContract* logisticsContract, const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const enum ContractPhase current_phase, const Product product, const QUANTITY_INT quantity);

void processTickLogisticsContract(LogisticsContract* logisticsContract);
void cleanContract(LogisticsContract* logisticsContract);

#endif