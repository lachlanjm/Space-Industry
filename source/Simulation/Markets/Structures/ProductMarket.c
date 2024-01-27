#include "ProductMarket.h"

ProductMarket* newProductMarket(const Product product_type)
{
	ProductMarket* productMarket = (ProductMarket*) malloc(1 * sizeof(ProductMarket));

	productMarket->product_type = product_type;
	productMarket->lowest_sell_order = NULL;
	productMarket->highest_buy_order = NULL;

	return productMarket;
}

void assignNewProductMarket(ProductMarket* productMarket, const Product product_type)
{
	productMarket->product_type = product_type;
	productMarket->lowest_sell_order = NULL;
	productMarket->highest_buy_order = NULL;
}

void addSellOrder(ProductMarket* productMarket, Order* new_order)
{
	// TODO MAKE THE ALGO. AVL
	Order* base_order = productMarket->lowest_sell_order;
	if (base_order == NULL)
	{
		productMarket->lowest_sell_order = new_order;
		new_order->prev_order = NULL;
		new_order->left_order = NULL;
		new_order->right_order = NULL;
		return;
	}

	while (1) 
	{
		if (base_order->left_order == NULL)
		{
			base_order->left_order = new_order;
			new_order->prev_order = base_order;
			break;
		}
		if (base_order->right_order == NULL)
		{
			base_order->right_order = new_order;
			new_order->prev_order = base_order;
			break;
		}
		base_order = base_order->left_order;
	}

	new_order->left_order = NULL;
	new_order->right_order = NULL;

	while (1)
	{
		if (new_order->left_order != NULL)
		{
			if (new_order->price >= new_order->left_order->price)
			{
				swap_orders(new_order, new_order->left_order);
				if (new_order->prev_order->prev_order == NULL)
				{
					productMarket->lowest_sell_order = new_order->prev_order;
				}
				continue;
			}
		}
		if (new_order->right_order != NULL)
		{
			if (new_order->price >= new_order->right_order->price)
			{
				swap_orders(new_order, new_order->right_order);
				if (new_order->prev_order->prev_order == NULL)
				{
					productMarket->lowest_sell_order = new_order->prev_order;
				}
				continue;
			}
		}
		break;
	}
}

Order* addNewSellOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
	Order* order = newOrder(offering_factory, offer_num, price);
	addSellOrder(productMarket, order);
	return order;
}

void addBuyOrder(ProductMarket* productMarket, Order* new_order)
{
	// TODO MAKE THE ALGO. AVL
	Order* base_order = productMarket->highest_buy_order;
	if (base_order == NULL)
	{
		productMarket->highest_buy_order = new_order;
		new_order->prev_order = NULL;
		new_order->left_order = NULL;
		new_order->right_order = NULL;
		return;
	}

	while (1) 
	{
		if (base_order->left_order == NULL)
		{
			base_order->left_order = new_order;
			new_order->prev_order = base_order;
			break;
		}
		if (base_order->right_order == NULL)
		{
			base_order->right_order = new_order;
			new_order->prev_order = base_order;
			break;
		}
		base_order = base_order->left_order;
	}

	new_order->left_order = NULL;
	new_order->right_order = NULL;

	while (1)
	{
		if (new_order->left_order != NULL)
		{
			if (new_order->price <= new_order->left_order->price)
			{
				swap_orders(new_order, new_order->left_order);
				if (new_order->prev_order->prev_order == NULL)
				{
					productMarket->highest_buy_order = new_order->prev_order;
				}
				continue;
			}
		}
		if (new_order->right_order != NULL)
		{
			if (new_order->price <= new_order->right_order->price)
			{
				swap_orders(new_order, new_order->right_order);
				if (new_order->prev_order->prev_order == NULL)
				{
					productMarket->highest_buy_order = new_order->prev_order;
				}
				continue;
			}
		}
		break;
	}
}

Order* addNewBuyOrder(ProductMarket* productMarket, const Factory* offering_factory, const QUANTITY_INT offer_num, const uint_fast16_t price)
{
	Order* order = newOrder(offering_factory, offer_num, price);
	addBuyOrder(productMarket, order);
	return order;
}

void removeBuyOrder(ProductMarket* productMarket, Order* old_order)
{
	// Don't remove from factory, a quant of 0 === off the market
	while (1) 
	{
		if (old_order->right_order != NULL)
		{
			swap_orders(old_order, old_order->right_order);
			if (old_order->prev_order->prev_order == NULL)
			{
				productMarket->highest_buy_order = old_order->prev_order;
			}
			continue;
		}
		if (old_order->left_order != NULL)
		{
			swap_orders(old_order, old_order->left_order);
			if (old_order->prev_order->prev_order == NULL)
			{
				productMarket->highest_buy_order = old_order->prev_order;
			}
			continue;
		}
		break;
	}

	old_order->offer_num = 0;

	if (old_order->prev_order == NULL)
	{
		productMarket->highest_buy_order = NULL;
	}
	else if (old_order == old_order->prev_order->left_order)
	{
		old_order->prev_order->left_order = NULL;
	}
	else
	{
		old_order->prev_order->right_order = NULL;
	}

	old_order->prev_order = NULL;
}

void removeSellOrder(ProductMarket* productMarket, Order* old_order)
{
	// Don't remove from factory, a quant of 0 === off the market
	while (1) 
	{
		if (old_order->right_order != NULL)
		{
			swap_orders(old_order, old_order->right_order);
			if (old_order->prev_order->prev_order == NULL)
			{
				productMarket->lowest_sell_order = old_order->prev_order;
			}
			continue;
		}
		if (old_order->left_order != NULL)
		{
			swap_orders(old_order, old_order->left_order);
			if (old_order->prev_order->prev_order == NULL)
			{
				productMarket->lowest_sell_order = old_order->prev_order;
			}
			continue;
		}
		break;
	}
	
	old_order->offer_num = 0;

	if (old_order->prev_order == NULL)
	{
		productMarket->lowest_sell_order = NULL;
	}
	else if (old_order == old_order->prev_order->left_order)
	{
		old_order->prev_order->left_order = NULL;
	}
	else
	{
		old_order->prev_order->right_order = NULL;
	}

	old_order->prev_order = NULL;
}

QUANTITY_INT match_orders(ProductMarket* selling_market, Order* selling_order, ProductMarket* buying_market, Order* buying_order)
{
	QUANTITY_INT exchanged_num;
	if (selling_order->offer_num > buying_order->offer_num)
	{
		exchanged_num = buying_order->offer_num;
	}
	else
	{
		exchanged_num = selling_order->offer_num;
	}

	selling_order->offer_num -= exchanged_num;
	buying_order->offer_num -= exchanged_num;

	if (selling_order->offer_num == 0)
	{
		removeSellOrder(selling_market, selling_order);
	}

	if (buying_order->offer_num == 0)
	{
		removeBuyOrder(buying_market, buying_order);
	}

	return exchanged_num;
}

void swap_orders(Order* parent_order, Order* child_order)
{
	if (parent_order->prev_order != NULL)
	{
		if (parent_order == parent_order->prev_order->left_order)
		{
			parent_order->prev_order->left_order = child_order;
		}
		else
		{
			parent_order->prev_order->right_order = child_order;
		}
	}

	child_order->prev_order = parent_order->prev_order;

	if (child_order == parent_order->left_order)
	{
		parent_order->left_order = child_order->left_order;
		child_order->left_order = child_order->right_order; // tmp var storage
		child_order->right_order = parent_order->right_order;
		parent_order->right_order = child_order->left_order;
		child_order->left_order = parent_order;

		if (child_order->right_order != NULL)
		{
			child_order->right_order->prev_order = child_order;
		}
	}
	else
	{
		parent_order->right_order = child_order->right_order;
		child_order->right_order = child_order->left_order; // tmp var storage
		child_order->left_order = parent_order->left_order;
		parent_order->left_order = child_order->right_order;
		child_order->right_order = parent_order;

		if (child_order->left_order != NULL)
		{
			child_order->left_order->prev_order = child_order;
		}
	}

	if (parent_order->left_order != NULL)
	{
		parent_order->left_order->prev_order = parent_order;
	}
	if (parent_order->right_order != NULL)
	{
		parent_order->right_order->prev_order = parent_order;
	}

	parent_order->prev_order = child_order;
}

void resetBuyOrder(ProductMarket* productMarket, Order* reset_order)
{
	while (1)
	{
		if (reset_order->prev_order == NULL)
		{
			productMarket->highest_buy_order = reset_order;
			break;
		}
		if (reset_order->price > reset_order->prev_order->price)
		{
			swap_orders(reset_order->prev_order, reset_order);
			continue;
		}
		break;
	}
	while (1)
	{
		if (reset_order->left_order != NULL)
		{
			if (reset_order->price <= reset_order->left_order->price)
			{
				swap_orders(reset_order, reset_order->left_order);
				if (reset_order->prev_order->prev_order == NULL)
				{
					productMarket->highest_buy_order = reset_order->prev_order;
				}
				continue;
			}
		}
		if (reset_order->right_order != NULL)
		{
			if (reset_order->price <= reset_order->right_order->price)
			{
				swap_orders(reset_order, reset_order->right_order);
				if (reset_order->prev_order->prev_order == NULL)
				{
					productMarket->highest_buy_order = reset_order->prev_order;
				}
				continue;
			}
		}
		break;
	}
}

void resetSellOrder(ProductMarket* productMarket, Order* reset_order)
{
	while (1)
	{
		if (reset_order->prev_order == NULL)
		{
			productMarket->lowest_sell_order = reset_order;
			break;
		}
		if (reset_order->price < reset_order->prev_order->price)
		{
			swap_orders(reset_order->prev_order, reset_order);
			continue;
		}
		break;
	}
	while (1)
	{
		if (reset_order->left_order != NULL)
		{
			if (reset_order->price >= reset_order->left_order->price)
			{
				swap_orders(reset_order, reset_order->left_order);
				if (reset_order->prev_order->prev_order == NULL)
				{
					productMarket->lowest_sell_order = reset_order->prev_order;
				}
				continue;
			}
		}
		if (reset_order->right_order != NULL)
		{
			if (reset_order->price >= reset_order->right_order->price)
			{
				swap_orders(reset_order, reset_order->right_order);
				if (reset_order->prev_order->prev_order == NULL)
				{
					productMarket->lowest_sell_order = reset_order->prev_order;
				}
				continue;
			}
		}
		break;
	}
}
