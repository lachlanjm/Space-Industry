#include "LocalPopulation.h"

static LOCAL_POPULATION_ID_INT id_next = 0;

LocalPopulation* newLocalPopulation(const TransportNode location, const uint32_t population_number)
{
	LocalPopulation* population = calloc(1, sizeof(LocalPopulation));
	assignLocalPopulationValues(population, location, population_number);
	return population;
}

void assignLocalPopulationValues(LocalPopulation* population, const TransportNode location, const uint32_t population_number)
{
	population->population_number = population_number;
	assignFactoryValues(&population->population_centre, Population_Consumption, location);

	population->id = id_next++;
}

void assignLoadIdLocalPopulation(LocalPopulation* obj, const int id)
{
	obj->id = id;
	if (id >= id_next)
	{
		id_next = id + 1;
	}
}

// TODO TBU: CUSTOM MANAGEMENT OF FACTORY
void processTickLocalPopulation(LocalPopulation* population)
{
	population->population_centre.processing_speed = population->population_number / CONSUMPTION_RATE_DIVISOR;
	processTickFactory(&population->population_centre);
}

void cleanLocalPopulation(LocalPopulation* population)
{
	cleanFactory(&population->population_centre);
}
