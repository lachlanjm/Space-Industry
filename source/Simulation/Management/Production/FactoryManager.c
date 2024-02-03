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

		if (STOCKPILE_FULL - ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			if (factoryManager->controlled_factory.orders_in[i].offer_num == 0)
			{
				// Add to market
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
				factoryManager->controlled_factory.orders_in[i].price *= DECREASE_PRICE_FACTOR;
				resetBuyOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
					&factoryManager->controlled_factory.orders_in[i]
				);
			}
			else if (DESIRED_STOCKPILE_MIN > stockpile_ordered_quantity)
			{
				// Raise offered price
				factoryManager->controlled_factory.orders_in[i].price *= INCREASE_PRICE_FACTOR;
				resetBuyOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
					&factoryManager->controlled_factory.orders_in[i]
				);
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
		if (ORDER_QUANTITY_MIN < stockpile_free_quantity)
		{
			if (factoryManager->controlled_factory.orders_out[i].offer_num == 0)
			{
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
				factoryManager->controlled_factory.orders_out[i].price *= DECREASE_PRICE_FACTOR;
				resetSellOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
					&factoryManager->controlled_factory.orders_out[i]
				);
			}
			else if (DESIRED_STOCKPILE_MIN > stockpile_free_quantity)
			{
				// Raise selling price
				factoryManager->controlled_factory.orders_out[i].price *= INCREASE_PRICE_FACTOR;
				resetSellOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
					&factoryManager->controlled_factory.orders_out[i]
				);
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

		if (STOCKPILE_FULL - ORDER_QUANTITY_MIN > stockpile_ordered_quantity)
		{
			if (factoryManager->controlled_factory.orders_in[i].offer_num == 0)
			{
				// Add to market
				addBuyOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_in[i].product_type),
					&factoryManager->controlled_factory.orders_in[i]
				);
			}
			factoryManager->controlled_factory.orders_in[i].offer_num = STOCKPILE_FULL - stockpile_ordered_quantity;
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
		if (ORDER_QUANTITY_MIN < stockpile_free_quantity)
		{
			if (factoryManager->controlled_factory.orders_out[i].offer_num == 0)
			{
				// Add to market
				addSellOrder(
					getProductMarketAtLocation(factoryManager->controlled_factory.location, factoryManager->controlled_factory.stockpiles_out[i].product_type),
					&factoryManager->controlled_factory.orders_out[i]
				);
			}
			factoryManager->controlled_factory.orders_out[i].offer_num = stockpile_free_quantity;
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
