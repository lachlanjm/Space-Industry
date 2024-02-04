#include "FactoryManager.h"

static FACTORY_MANAGER_ID_INT id_next = 0;

void assignFactoryManagerValues(FactoryManager* factoryManager, const ProductionRecipe productionRecipe, const TransportNode location)
{
	assignFactoryValues(&factoryManager->controlled_factory, productionRecipe, location);
	factoryManager->id = id_next++;
} 

void updateOfferedPrices(FactoryManager* factoryManager)
{
	for (int i = 0; i < factoryManager->controlled_factory.stockpiles_in_num; i++)
	{
		QUANTITY_INT stockpile_ordered_quantity = 
			factoryManager->controlled_factory.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&factoryManager->controlled_factory, 
				factoryManager->controlled_factory.stockpiles_in[i].product_type
		);

		if (FM_STOCKPILE_FULL - FM_ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			if (factoryManager->controlled_factory.orders_in[i].offer_num == 0)
			{
				// Add to market
				if (addBuyOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
					&factoryManager->controlled_factory.orders_in[i])
				) {
					printf("Failed to add buy order\n");
				}
			}
			factoryManager->controlled_factory.orders_in[i].offer_num = FM_STOCKPILE_FULL - stockpile_ordered_quantity;
		}

		if (factoryManager->controlled_factory.orders_in[i].offer_num > 0)
		{
			if (FM_DESIRED_STOCKPILE_MAX < stockpile_ordered_quantity)
			{
				// Lower offered price
				factoryManager->controlled_factory.orders_in[i].price *= FM_DECREASE_PRICE_FACTOR;
				if (resetBuyOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
					&factoryManager->controlled_factory.orders_in[i])
				) {
					printf("Failed to reset buy order\n");
				}
			}
			else if (FM_DESIRED_STOCKPILE_MIN > stockpile_ordered_quantity)
			{
				// Raise offered price
				factoryManager->controlled_factory.orders_in[i].price *= FM_INCREASE_PRICE_FACTOR;
				if (resetBuyOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
					&factoryManager->controlled_factory.orders_in[i])
				) {
					printf("Failed to reset buy order\n");
				}
			}
		}
	}
	for (int i = 0; i < factoryManager->controlled_factory.stockpiles_out_num; i++)
	{
		QUANTITY_INT stockpile_free_quantity = 
			factoryManager->controlled_factory.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&factoryManager->controlled_factory, 
				factoryManager->controlled_factory.stockpiles_out[i].product_type
		);
		if (FM_ORDER_QUANTITY_MIN < stockpile_free_quantity)
		{
			if (factoryManager->controlled_factory.orders_out[i].offer_num == 0)
			{
				// Add to market
				if (addSellOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
					&factoryManager->controlled_factory.orders_out[i])
				) {
					printf("Failed to add sell order\n");
				}
			}
			factoryManager->controlled_factory.orders_out[i].offer_num = stockpile_free_quantity;
		}

		if (factoryManager->controlled_factory.orders_out[i].offer_num > 0)
		{
			if (FM_DESIRED_STOCKPILE_MAX < stockpile_free_quantity)
			{
				// Lower selling price
				factoryManager->controlled_factory.orders_out[i].price *= FM_DECREASE_PRICE_FACTOR;
				if (resetSellOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
					&factoryManager->controlled_factory.orders_out[i])
				) {
					printf("Failed to reset sell order\n");
				}
			}
			else if (FM_DESIRED_STOCKPILE_MIN > stockpile_free_quantity)
			{
				// Raise selling price
				factoryManager->controlled_factory.orders_out[i].price *= FM_INCREASE_PRICE_FACTOR;
				if (resetSellOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
					&factoryManager->controlled_factory.orders_out[i])
				) {
					printf("Failed to reset sell order\n");
				}
			}
		}
	}
}

void loadFactoryManagerAssignOrders(FactoryManager* factoryManager)
{
	for (int i = 0; i < factoryManager->controlled_factory.stockpiles_in_num; i++)
	{
		QUANTITY_INT stockpile_ordered_quantity = 
			factoryManager->controlled_factory.stockpiles_in[i].quantity
			+ *getOrderedInQuantity(
				&factoryManager->controlled_factory, 
				factoryManager->controlled_factory.stockpiles_in[i].product_type
		);

		if (FM_STOCKPILE_FULL - FM_ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			// Add to market
			 if (addBuyOrder(
				getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
				&factoryManager->controlled_factory.orders_in[i])
			) {
				printf("Failed to add buy order\n");
			}
			factoryManager->controlled_factory.orders_in[i].offer_num = FM_STOCKPILE_FULL - stockpile_ordered_quantity;
		}
		else 
		{
			factoryManager->controlled_factory.orders_in[i].offer_num = 0;
		}
	}

	for (int i = 0; i < factoryManager->controlled_factory.stockpiles_out_num; i++)
	{
		QUANTITY_INT stockpile_free_quantity = 
			factoryManager->controlled_factory.stockpiles_out[i].quantity
			- *getOrderedOutQuantity(
				&factoryManager->controlled_factory, 
				factoryManager->controlled_factory.stockpiles_out[i].product_type
		);
		if (FM_ORDER_QUANTITY_MIN < stockpile_free_quantity)
		{
			// Add to market
			if (addSellOrder(
				getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
				&factoryManager->controlled_factory.orders_out[i])
			) {
				printf("Failed to add sell order\n");
			}
			factoryManager->controlled_factory.orders_out[i].offer_num = stockpile_free_quantity;
		}
		else 
		{
			factoryManager->controlled_factory.orders_out[i].offer_num = 0;
		}
	}
}

void assignLoadIdFactoryManager(FactoryManager* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void processTickFactoryManager(FactoryManager* factoryManager)
{
	updateOfferedPrices(factoryManager);
	processTickFactory(&factoryManager->controlled_factory);
}

void cleanFactoryManager(FactoryManager* factoryManager)
{
	cleanFactory(&factoryManager->controlled_factory);
}
