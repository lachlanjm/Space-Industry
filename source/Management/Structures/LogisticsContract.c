#include "LogisticsContract.h"

inline LogisticsContract* newLogisticsContract(const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
    LogisticsContract* logisticsContract = (LogisticsContract*) malloc(1 * sizeof(LogisticsContract));
    assignNewLogisticsContractValues(logisticsContract, assigned_vehicle, selling_factory, buying_factory, product, quantity);
    return logisticsContract;
}

inline void assignNewLogisticsContractValues(LogisticsContract* logisticsContract, const Vehicle* assigned_vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
    logisticsContract->assigned_vehicle = assigned_vehicle;
    logisticsContract->selling_factory = selling_factory;
    logisticsContract->buying_factory = buying_factory;
    logisticsContract->product = product;
    logisticsContract->quantity = quantity;
}


void cleanContract(LogisticsContract* logisticsContract)
{

}
