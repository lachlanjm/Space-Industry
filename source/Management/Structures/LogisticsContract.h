#ifndef LOGISTICS_CONTRACT_H
#define LOGISTICS_CONTRACT_H

#include "..\..\Transport\Structures\Vehicle.h"
#include "..\..\Production\Structures\Factory.h"
#include "..\..\Production\Enums\Product.h"

typedef struct LogisticsContract 
{
    // uint_fast16_t vehicle_num;
    Vehicle* assigned_vehicle; // TODO make array

    Factory* selling_factory;
    Factory* buying_factory;

    Product product;
    QUANTITY_INT quantity;
} LogisticsContract;

inline LogisticsContract* newLogisticsContract(const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity);
inline void assignNewLogisticsContractValues(LogisticsContract* logisticsContract, const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity);

void cleanContract(LogisticsContract* logisticsContract);

#endif