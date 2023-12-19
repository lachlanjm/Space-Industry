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

inline void addNewLogisticsContract(LogisticsManager* logisticsManager, const Vehicle* vehicle, const Factory* selling_factory, const Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
    logisticsManager->contracts = realloc(logisticsManager->contracts, ++logisticsManager->contracts_num * sizeof(LogisticsContract));
    assignNewLogisticsContractValues(&logisticsManager->contracts[logisticsManager->contracts_num - 1], vehicle, selling_factory, buying_factory, product, quantity);
}

void updateDistToPriceEff(LogisticsManager* logisticsManager)
{
    for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
    {
        for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
        {
            for (int product = 0; product < PRODUCT_COUNT; product++)
            {
                if (getTotalDistance(from, to) == 0)
                {
                    logisticsManager->dist_to_price_eff[from][to][product] =
                    (float) (getProductMarketAtLocation(to, product)->highest_buy_order->price 
                    - getProductMarketAtLocation(from, product)->lowest_sell_order->price);
                }
                else 
                {
                    logisticsManager->dist_to_price_eff[from][to][product] =
                    (float) (getProductMarketAtLocation(to, product)->highest_buy_order->price 
                    - getProductMarketAtLocation(from, product)->lowest_sell_order->price)
                    / (float)getTotalDistance(from, to);
                }
            }
        }
    }
}
    
void assignFreeVehicles(LogisticsManager* logisticsManager)
{
    for (int i = 0; i < logisticsManager->vehicles_num; i++)
    {
        if (logisticsManager->vehicles[i].end_location == NULL)
        {
            assignNewLogisticsContract(logisticsManager, &logisticsManager->vehicles[i]);
            updateDistToPriceEff(logisticsManager);
        }
    }
}

void assignNewLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle)
{
    int from_max = -1;
    int to_max = -1;
    int product_max = -1;
    int eff_max = 0;

    for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
    {
        for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
        {
            for (int product = 0; product < PRODUCT_COUNT; product++)
            {
                if (logisticsManager->dist_to_price_eff[from][to][product] > eff_max)
                {
                    from_max = from;
                    to_max = to;
                    product_max = product;
                    eff_max = logisticsManager->dist_to_price_eff[from][to][product];
                }
            }
        }
    }

    QUANTITY_INT quantity = match_orders(
        getProductMarketAtLocation(from_max, product_max), 
        getProductMarketAtLocation(from_max, product_max)->lowest_sell_order,
        getProductMarketAtLocation(to_max, product_max),
        getProductMarketAtLocation(to_max, product_max)->highest_buy_order
    );

    addNewLogisticsContract(
        logisticsManager,
        vehicle,
        getProductMarketAtLocation(from_max, product_max)->lowest_sell_order->offering_factory,
        getProductMarketAtLocation(to_max, product_max)->highest_buy_order->offering_factory,
        product_max,
        quantity
    );
}

void processTickLogisticsManagerContracts(LogisticsManager* logisticsManager)
{
    // Search and add contracts
    // TODO calc only when needed and save between LMs (static?) !!!!!!!!!!!
    updateDistToPriceEff(logisticsManager);
    assignFreeVehicles(logisticsManager);

    // Tick contracts
    for (int i = 0; i < logisticsManager->contracts_num; i++)
    {
        processTickLogisticsContract(&logisticsManager->contracts[i]);
    }
}

void processTickLogisticsManagerVehicles(LogisticsManager* logisticsManager)
{
    // Tick vehicles
    for (int i = 0; i < logisticsManager->vehicles_num; i++)
    {
        processTickVehicle(&logisticsManager->vehicles[i]);
    }
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
    free(logisticsManager->contracts);
}

