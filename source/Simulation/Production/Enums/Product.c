#include "Product.h"

const static char* __product_names_arr[] =
{
	"Iron Ore", 
	"Iron", 
	"Coal", 
	"Carbon", 
	"Carbon Monoxide", 
	"Carbon Dioxide", 
	"Carbonic Acid", 
	"Steel", 
	"Copper Ore", 
	"Copper", 
	"Copper Wire", 
	"Sand", 
	"Silicon", 
	"Water", 
	"Heavy Water", 
	"Hydrogen", 
	"Deuterium", 
	"Oxygen", 
	"Sulfur", 
	"Sulfur Dioxide", 
	"Crude Oil", 
	"Petroleum Gas", 
	"Gasoline", 
	"Naptha", 
	"Plastic", 
	"Kerosene", 
	"Aviation Fuel", 
	"Diesel", 
	"Fuel Oil", 
	"Lubricating Oil", 
	"Bitumen", 
	"Asphalt", 
	"Rock", 
	"Crushed Rock", 
	"Lime"
};
const char* getNameProduct(const Product product) {
	return __product_names_arr[product];
}

const static char* __product_states_arr[] =
{
	"Solid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Gas", 
	"Gas", 
	"Liquid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Liquid", 
	"Liquid", 
	"Gas", 
	"Gas", 
	"Gas", 
	"Solid", 
	"Gas", 
	"Liquid", 
	"Gas", 
	"Liquid", 
	"Solid", 
	"Solid", 
	"Liquid", 
	"Liquid", 
	"Liquid", 
	"Liquid", 
	"Liquid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Solid", 
	"Solid"
};
const char* getState(const Product product) {
	return __product_states_arr[product];
}

const static char* __product_short_arr[] =
{
	"Fe-", 
	"Fe", 
	"C-", 
	"C", 
	"CO", 
	"CO2", 
	"H2CO3", 
	"FeC", 
	"Cu-", 
	"Cu", 
	"Wire", 
	"SiO2", 
	"Si", 
	"H2O", 
	"D2O", 
	"H", 
	"D", 
	"O", 
	"S", 
	"SO2", 
	"Crude", 
	"Petrol", 
	"Gas", 
	"Nap", 
	"Plas", 
	"Kero", 
	"AvFu", 
	"Dsl", 
	"Fuel", 
	"Lube", 
	"Bitu", 
	"Asph", 
	"Rock", 
	"Crush", 
	"Lime"
};
const char* getShort(const Product product) {
	return __product_short_arr[product];
}

const static char* __product_category_arr[] =
{
	"Raw", 
	"Elemental", 
	"Raw", 
	"Elemental", 
	"Molecule", 
	"Molecule", 
	"Molecule", 
	"Refined", 
	"Raw", 
	"Elemental", 
	"Refined", 
	"Raw", 
	"Elemental", 
	"Raw", 
	"Raw", 
	"Elemental", 
	"Elemental", 
	"Elemental", 
	"Elemental", 
	"Molecule", 
	"Raw", 
	"Refined", 
	"Refined", 
	"Refined", 
	"Intermediate", 
	"Refined", 
	"Fuel", 
	"Fuel", 
	"Refined", 
	"Refined", 
	"Refined", 
	"Intermediate", 
	"Raw", 
	"Refined", 
	"Raw"
};
const char* getCategory(const Product product) {
	return __product_category_arr[product];
}

const static uint_fast16_t __product_greenhouse_arr[] =
{
	+0, 
	+0, 
	+0, 
	+0, 
	+2, 
	+1, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+11, 
	+11, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0, 
	+0
};
const uint_fast16_t getGreenhouse(const Product product) {
	return __product_greenhouse_arr[product];
}

const static float __product_acididty_arr[] =
{
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	4.68f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	7.0f, 
	7.44f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	10.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f, 
	0.0f
};
const float getAcidity(const Product product) {
	return __product_acididty_arr[product];
}

