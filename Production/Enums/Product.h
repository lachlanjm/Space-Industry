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
	Nitrogen_Dioxide
} Product;

char* getName(const Product product);
char* getState(const Product product);
char* getShort(const Product product);
char* getCategory(const Product product);
uint_fast16_t getGreenhouse(const Product product);
float getAcidity(const Product product);


#endif