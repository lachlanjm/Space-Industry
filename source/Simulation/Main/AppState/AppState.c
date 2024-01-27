#include "AppState.h"

void processTickAppState(AppState* appState)
{
    for (int i = 0; i < appState->factory_managers_num; i++)
    {
        printf("\tFM - %d\n", i);
        processTickFactoryManager(&appState->factory_managers[i]);
    }
    printf("\tCompleted FMs\n");

    printf("\tContract phase for LM - %d\n", appState->logistics_managers_next_process_tick_index);
    processTickLogisticsManagerContracts(&appState->logistics_managers[appState->logistics_managers_next_process_tick_index]);
    appState->logistics_managers_next_process_tick_index = (++appState->logistics_managers_next_process_tick_index) % appState->logistics_managers_num;
    printf("\tCompleted Contract Phase\n");

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        printf("\tLM - %d\n", i);
        processTickLogisticsManagerVehicles(&appState->logistics_managers[i]);
    }
    printf("\tCompleted LMs\n");

    //display_product_heaps();
}

void cleanAppState(AppState* appState)
{
    for (int i = 0; i < appState->factory_managers_num; i++)
    {
        cleanFactoryManager(&appState->factory_managers[i]);
    }
    free(appState->factory_managers);

    for (int i = 0; i < appState->logistics_managers_num; i++)
    {
        cleanLogisticsManager(&appState->logistics_managers[i]);
    }
    free(appState->logistics_managers);
}

void display_product_heaps()
{
    printf("\nPMs:\n");
    //for (int loc = 0; loc < TRANSPORT_NODE_COUNT; loc++)
    for (int loc = 0; loc < 1; loc++)
    {
        for (int product = 0; product < PRODUCT_COUNT; product++)
        {
            printf("Loc: %d\tProd:%d\n", loc, product);
            disp_heap(getProductMarketAtLocation(loc, product));
        }
    }
}

void disp_heap(ProductMarket* market)
{
    printf("Highest Buy Order:\n");
    if (market->highest_buy_order != NULL)
    {
        disp_order(market->highest_buy_order, 0);
    }
    else
    {
        printf("\tNo orders\n");
    }

    printf("Lowest Sell Order:\n");
    if (market->lowest_sell_order != NULL)
    {
        disp_order(market->lowest_sell_order, 0);
    }
    else
    {
        printf("\tNo orders\n");
    }
}

void disp_order(Order* order, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("--");
    }
    printf("Price: %u\t Quantity %u\t Addr:%p\n", order->price, order->offer_num, order);
    
    if (order->left_order != NULL)
    {
        disp_order(order->left_order, depth + 1);
    }
    else 
    {
        for (int i = 0; i < depth + 1; i++)
        {
            printf("--");
        }
        printf("No left order\n");
    }
    if (order->right_order != NULL)
    {
        disp_order(order->right_order, depth + 1);
    }
    else 
    {
        for (int i = 0; i < depth + 1; i++)
        {
            printf("--");
        }
        printf("No right order\n");
    }
}