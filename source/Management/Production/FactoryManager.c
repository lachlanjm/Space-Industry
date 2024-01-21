#include "FactoryManager.h"

void assignFactoryManagerValues(FactoryManager* factoryManager, const ProductionRecipe productionRecipe, const TransportNode location)
{
    assignFactoryValues(&factoryManager->controlled_factory, productionRecipe, location);
}

void updateOfferedPrices(FactoryManager* factoryManager)
{
    for (int i = 0; i < factoryManager->controlled_factory.stockpiles_in_num; i++)
    {
        printf("\t\tStockpile in num - %d\n", i);
        QUANTITY_INT stockpile_ordered_quantity = 
            factoryManager->controlled_factory.stockpiles_in[i].quantity
            + *getOrderedInQuantity(
                &factoryManager->controlled_factory, 
                factoryManager->controlled_factory.stockpiles_in[i].product_type
        );

        if (STOCKPILE_FULL - ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
        {
            printf("\t\t\tUpdate buying offered quantity - %x: offer_num: %d\n", &factoryManager->controlled_factory.orders_in[i], factoryManager->controlled_factory.orders_in[i].offer_num);
            if (factoryManager->controlled_factory.orders_in[i].offer_num == 0)
            {
                // Add to market
                printf("\t\t\tAdding buying offer: %x\n", &factoryManager->controlled_factory.orders_in[i]);
                addBuyOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
                    &factoryManager->controlled_factory.orders_in[i]
                );
            }
            factoryManager->controlled_factory.orders_in[i].offer_num = STOCKPILE_FULL - stockpile_ordered_quantity;
        }

        if (factoryManager->controlled_factory.orders_in[i].offer_num > 0)
        {
            if (DESIRED_STOCKPILE_MAX < stockpile_ordered_quantity)
            {
                // Lower offered price
                printf("\t\t\tLower buying price\n");
                factoryManager->controlled_factory.orders_in[i].price *= DECREASE_PRICE_FACTOR;
                resetBuyOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
                    &factoryManager->controlled_factory.orders_in[i]
                );
            }
            else if (DESIRED_STOCKPILE_MIN > stockpile_ordered_quantity)
            {
                // Raise offered price
                printf("\t\t\tRaise buying price\n");
                factoryManager->controlled_factory.orders_in[i].price *= INCREASE_PRICE_FACTOR;
                resetBuyOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
                    &factoryManager->controlled_factory.orders_in[i]
                );
            }
        }
        printf("\t\t\tQuantity - %d\tPrice - %d\n", factoryManager->controlled_factory.stockpiles_in[i].quantity, factoryManager->controlled_factory.orders_in[i].price);
    }

    for (int i = 0; i < factoryManager->controlled_factory.stockpiles_out_num; i++)
    {
        printf("\t\tStockpile out num - %d\n", i);
        QUANTITY_INT stockpile_free_quantity = 
            factoryManager->controlled_factory.stockpiles_out[i].quantity
            - *getOrderedOutQuantity(
                &factoryManager->controlled_factory, 
                factoryManager->controlled_factory.stockpiles_out[i].product_type
        );
        if (ORDER_QUANTITY_MIN < stockpile_free_quantity)
        {
            printf("\t\t\tUpdate selling offered quantity\n");
            if (factoryManager->controlled_factory.orders_out[i].offer_num == 0)
            {
                printf("\t\t\tAdding selling offer: %x\n", &factoryManager->controlled_factory.orders_out[i]);
                // Add to market
                addSellOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
                    &factoryManager->controlled_factory.orders_out[i]
                );
            }
            factoryManager->controlled_factory.orders_out[i].offer_num = stockpile_free_quantity;
        }

        if (factoryManager->controlled_factory.orders_out[i].offer_num > 0)
        {
            if (DESIRED_STOCKPILE_MAX < stockpile_free_quantity)
            {
                // Lower selling price
                printf("\t\t\tLower selling Price\n");
                factoryManager->controlled_factory.orders_out[i].price *= DECREASE_PRICE_FACTOR;
                resetSellOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
                    &factoryManager->controlled_factory.orders_out[i]
                );
            }
            else if (DESIRED_STOCKPILE_MIN > stockpile_free_quantity)
            {
                // Raise selling price
                printf("\t\t\tRaise selling Price\n");
                factoryManager->controlled_factory.orders_out[i].price *= INCREASE_PRICE_FACTOR;
                resetSellOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
                    &factoryManager->controlled_factory.orders_out[i]
                );
            }
        }
        
        printf("\t\t\tQuantity - %d\tPrice - %d\n", factoryManager->controlled_factory.stockpiles_out[i].quantity, factoryManager->controlled_factory.orders_out[i].price);
    }
}

void processTickFactoryManager(FactoryManager* factoryManager)
{
    updateOfferedPrices(factoryManager);
    printf("\t\tUpdated Offers\n");
    processTickFactory(&factoryManager->controlled_factory);
    printf("\t\tProcessed Ticks\n");
}

void cleanFactoryManager(FactoryManager* factoryManager)
{
    cleanFactory(&factoryManager->controlled_factory);
}
