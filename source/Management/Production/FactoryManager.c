#include "FactoryManager.h"

void updateOfferedPrices(FactoryManager* factoryManager)
{
    for (int i = 0; i < factoryManager->controlled_factory.stockpiles_in_num; i++)
    {
        if (STOCKPILE_FULL - ORDER_QUANTITY_MIN > factoryManager->controlled_factory.stockpiles_in[i].quantity)
        {
            if (factoryManager->controlled_factory.orders_in[i].offer_num == 0)
            {
                // Add to market
                addBuyOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
                    &factoryManager->controlled_factory.orders_in[i]
                );
            }
            factoryManager->controlled_factory.orders_in[i].offer_num = STOCKPILE_FULL - factoryManager->controlled_factory.stockpiles_in[i].quantity;
        }

        if (DESIRED_STOCKPILE_MAX < factoryManager->controlled_factory.stockpiles_in[i].quantity)
        {
            // Lower offered price
        }
        else if (DESIRED_STOCKPILE_MIN > factoryManager->controlled_factory.stockpiles_in[i].quantity)
        {
            // Raise offered price
        }
    }

    for (int i = 0; i < factoryManager->controlled_factory.stockpiles_out_num; i++)
    {
        if (ORDER_QUANTITY_MIN < factoryManager->controlled_factory.stockpiles_out[i].quantity)
        {
            if (factoryManager->controlled_factory.orders_out[i].offer_num == 0)
            {
                // Add to market
                addSellOrder(
                    getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
                    &factoryManager->controlled_factory.orders_in[i]
                );
            }
            factoryManager->controlled_factory.orders_out[i].offer_num = factoryManager->controlled_factory.stockpiles_out[i].quantity;
        }

        if (DESIRED_STOCKPILE_MAX < factoryManager->controlled_factory.stockpiles_out[i].quantity)
        {
            // Lower selling price
        }
        else if (DESIRED_STOCKPILE_MIN > factoryManager->controlled_factory.stockpiles_out[i].quantity)
        {
            // Raise selling price
        }
    }
}

