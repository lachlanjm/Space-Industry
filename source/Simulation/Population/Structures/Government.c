#include "Government.h"

static int location_count = 0;
static Government** __static_government_control = NULL;

void setGovernmentControlStatic(const int transport_node_count)
{
	__static_government_control = (Government**) calloc(transport_node_count, sizeof(Government*));
	location_count = transport_node_count;
}

Government* getGovernmentByLocation(const TransportNode location)
{
	return __static_government_control[location];
}

void setGovernmentControlByLocation(Government* government, const TransportNode location)
{
	if (__static_government_control[location] != NULL) 
	{
		__static_government_control[location]->controlled_local_population_num--;
	}
	__static_government_control[location] = government;
	government->controlled_local_population_num++;
}

void resetGovernmentControlByLocation(const TransportNode location)
{
	if (__static_government_control[location] != NULL) 
	{
		__static_government_control[location]->controlled_local_population_num--;
	}
	__static_government_control[location] = NULL;
}

void cleanGovernmentControlStatic(void)
{
	if (__static_government_control != NULL)
	{
		free(__static_government_control);
	}
	__static_government_control = NULL;
	location_count = 0;
}

static GOVERNMENT_ID_INT id_next = 0;
void assignGovernmentValues(Government* government, const int wealth)
{
	government->wealth = wealth;
	government->controlled_local_population_num = 0;

	government->id = id_next++;
}

void assignLoadIdGovernment(Government* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

void insertFundsGovernment(Government* government, const int funds)
{
	government->wealth += funds;
}

void withdrawFundsGovernment(Government* government, const int funds)
{
	if (government->wealth < funds) return; // reject payment
	government->wealth -= funds;
}

// TODO optimise runtime
void processTickGovernment(Government* government)
{
	const int welfare_payments = government->wealth / government->controlled_local_population_num;
	for (TransportNode curr_loc = 0; curr_loc<location_count;curr_loc++)
	{
		if (government == getGovernmentByLocation(curr_loc))
		{
			withdrawFundsGovernment(government, welfare_payments);
			insertFundsLocalPopulation(
				getLocalPopulationByLocation(curr_loc),
				welfare_payments
			);
		}
	}
}

void cleanGovernment(Government* government)
{
	// TBU
}
