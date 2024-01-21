#include "LogisticsManager.h"

LogisticsManager* newLogisticsManager(const uint_fast16_t vehicles_num)
{
    LogisticsManager* logisticsManager = (LogisticsManager*) malloc(1 * sizeof(LogisticsManager));
    assignNewLogisticsManagerValues(logisticsManager, vehicles_num);
    return logisticsManager;
}

void assignNewLogisticsManagerValues(LogisticsManager* logisticsManager, const uint_fast16_t vehicles_num)
{
    logisticsManager->vehicles_num = vehicles_num;

    logisticsManager->vehicles = (Vehicle*) realloc(logisticsManager->vehicles, vehicles_num * sizeof(Vehicle));

    for (int i = 0; i < logisticsManager->vehicles_num; i++)
    {
        assignNewVehicleValues(&logisticsManager->vehicles[i], 0);
    }

    logisticsManager->contracts_num = 0;
    logisticsManager->contracts = NULL;
}

void addNewLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle, Factory* selling_factory, Factory* buying_factory, const Product product, const QUANTITY_INT quantity)
{
    logisticsManager->contracts = realloc(logisticsManager->contracts, ++logisticsManager->contracts_num * sizeof(LogisticsContract));
    addOrderedOutQuantity(selling_factory, product, quantity);
    addOrderedInQuantity(buying_factory, product, quantity);
    assignNewLogisticsContractValues(&logisticsManager->contracts[logisticsManager->contracts_num - 1], vehicle, selling_factory, buying_factory, ASSIGNMENT, product, quantity);
}

static float __dist_to_price_eff__[TRANSPORT_NODE_COUNT][TRANSPORT_NODE_COUNT][PRODUCT_COUNT];
void update_dist_to_price_eff()
{
    for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
    {
        for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
        {
            for (int product = 0; product < PRODUCT_COUNT; product++)
            {
                if (getProductMarketAtLocation(to, product)->highest_buy_order != NULL
                    && getProductMarketAtLocation(from, product)->lowest_sell_order != NULL)
                {
                    if (getTotalDistance(from, to) == 0)
                    {
                        __dist_to_price_eff__[from][to][product] =
                        (float) (getProductMarketAtLocation(to, product)->highest_buy_order->price 
                        - getProductMarketAtLocation(from, product)->lowest_sell_order->price);
                    }
                    else 
                    {
                        __dist_to_price_eff__[from][to][product] =
                        (float) (getProductMarketAtLocation(to, product)->highest_buy_order->price 
                        - getProductMarketAtLocation(from, product)->lowest_sell_order->price)
                        / (float)getTotalDistance(from, to);
                    }
                }
                else
                {
                    __dist_to_price_eff__[from][to][product] = 0;
                }
            }
        }
    }
}

void update_dist_to_price_eff_product_filtered(int product)
{
    for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
    {
        for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
        {
            if (getProductMarketAtLocation(to, product)->highest_buy_order != NULL
                && getProductMarketAtLocation(from, product)->lowest_sell_order != NULL)
            {
                if (getTotalDistance(from, to) == 0)
                {
                    __dist_to_price_eff__[from][to][product] =
                    (float) (getProductMarketAtLocation(to, product)->highest_buy_order->price 
                    - getProductMarketAtLocation(from, product)->lowest_sell_order->price);
                }
                else 
                {
                    __dist_to_price_eff__[from][to][product] =
                    (float) (getProductMarketAtLocation(to, product)->highest_buy_order->price 
                    - getProductMarketAtLocation(from, product)->lowest_sell_order->price)
                    / (float)getTotalDistance(from, to);
                }
            }
            else
            {
                __dist_to_price_eff__[from][to][product] = 0;
            }
        }
    }
}
    
void assignFreeVehicles(LogisticsManager* logisticsManager)
{
    for (int i = 0; i < logisticsManager->vehicles_num; i++)
    {
        if (logisticsManager->vehicles[i].end_location == -1)
        {
            printf("\t\t\tAssiging new vehicle\n");
            assignNewLogisticsContract(logisticsManager, &logisticsManager->vehicles[i]);
        }
    }
}

// TODO: return value to indicate no new state and stop iterating for current tick
void assignNewLogisticsContract(LogisticsManager* logisticsManager, Vehicle* vehicle)
{
    int from_max = -1;
    int to_max = -1;
    int product_max = -1;
    int eff_max = 0;

    printf("\t\t\t\tChecking efficient route\n");
    for (int from = 0; from < TRANSPORT_NODE_COUNT; from++)
    {
        for (int to = 0; to < TRANSPORT_NODE_COUNT; to++)
        {
            for (int product = 0; product < PRODUCT_COUNT; product++)
            {
                if (__dist_to_price_eff__[from][to][product] > eff_max)
                {
                    from_max = from;
                    to_max = to;
                    product_max = product;
                    eff_max = __dist_to_price_eff__[from][to][product];
                }
            }
        }
    }

    if (from_max == -1)
    {
        printf("\t\t\t\tNo new valid route\n");
        return;
    }

    // TODO !!!! IMPROVE FLOW AND MEMORY ASSIGNMENT
    Factory* selling_factory = getProductMarketAtLocation(from_max, product_max)->lowest_sell_order->offering_factory;
    Factory* buying_factory = getProductMarketAtLocation(to_max, product_max)->highest_buy_order->offering_factory;

    printf("\t\t\t\tChecking quantity\n");
    QUANTITY_INT quantity = match_orders(
        getProductMarketAtLocation(from_max, product_max), 
        getProductMarketAtLocation(from_max, product_max)->lowest_sell_order,
        getProductMarketAtLocation(to_max, product_max),
        getProductMarketAtLocation(to_max, product_max)->highest_buy_order
    );

    printf("\t\t\t\tCreating contract: %x:%x:%d:%u:%u:%u\n", logisticsManager, vehicle, product_max, quantity, from_max, to_max);
    addNewLogisticsContract(
        logisticsManager,
        vehicle,
        selling_factory,
        buying_factory,
        product_max,
        quantity
    );

    printf("\t\t\t\tUpdating Eff. Map\n");
    update_dist_to_price_eff_product_filtered(product_max);
}

void processTickLogisticsManagerContracts(LogisticsManager* logisticsManager)
{
    // Search and add contracts
    printf("\t\tUpdating Dist Price Eff.\n");
    update_dist_to_price_eff();
    printf("\t\tAssigning free vehicles\n");
    assignFreeVehicles(logisticsManager);

    printf("\t\tTicking Contracts\n");
    // Tick contracts
    for (int i = 0; i < logisticsManager->contracts_num; i++)
    {
        processTickLogisticsContract(&logisticsManager->contracts[i]);
    }
    printf("\t\tCompleted Contracts\n");
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

