#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdint.h>
#include <stdlib.h>

typedef enum Product 
{
    Iron_Ore,
	Iron,
	Coal,
	Carbon,
	Carbon_Monoxide,
	Carbon_Dioxide,
	Carbonic_Acid,
	Steel,
	Copper_Ore,
	Copper,
	Copper_Wire,
	Sand,
	Silicon,
	Water,
	Heavy_Water,
	Hydrogen,
	Deuterium,
	Oxygen,
	Sulfur,
	Sulfur_Dioxide,
	Crude_Oil,
	Petroleum_Gas,
	Gasoline,
	Naptha,
	Plastic,
	Kerosene,
	Aviation_Fuel,
	Diesel,
	Fuel_Oil,
	Lubricating_Oil,
	Bitumen,
	Asphalt,
	Rock,
	Crushed_Rock,
	Lime,
	Nitrogen_Dioxide,
    PRODUCT_COUNT
} Product;

const char* getNameProduct(const Product product);
const char* getState(const Product product);
const char* getShort(const Product product);
const char* getCategory(const Product product);
const uint_fast16_t getGreenhouse(const Product product);
const float getAcidity(const Product product);


#endif