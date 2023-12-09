#include "Product.h"

char* getName(const Product product) {
    switch (product)
    {
    case Iron_Ore:
        return "Iron Ore";
    case Iron:
        return "Iron";
    case Coal:
        return "Coal";
    case Carbon:
        return "Carbon";
    case Carbon_Monoxide:
        return "Carbon Monoxide";
    case Carbon_Dioxide:
        return "Carbon Dioxide";
    case Carbonic_Acid:
        return "Carbonic Acid";
    case Steel:
        return "Steel";
    case Copper_Ore:
        return "Copper Ore";
    case Copper:
        return "Copper";
    case Copper_Wire:
        return "Copper Wire";
    case Sand:
        return "Sand";
    case Silicon:
        return "Silicon";
    case Water:
        return "Water";
    case Heavy_Water:
        return "Heavy Water";
    case Hydrogen:
        return "Hydrogen";
    case Deuterium:
        return "Deuterium";
    case Oxygen:
        return "Oxygen";
    case Sulfur:
        return "Sulfur";
    case Sulfur_Dioxide:
        return "Sulfur Dioxide";
    case Crude_Oil:
        return "Crude Oil";
    case Petroleum_Gas:
        return "Petroleum Gas";
    case Gasoline:
        return "Gasoline";
    case Naptha:
        return "Naptha";
    case Plastic:
        return "Plastic";
    case Kerosene:
        return "Kerosene";
    case Aviation_Fuel:
        return "Aviation Fuel";
    case Diesel:
        return "Diesel";
    case Fuel_Oil:
        return "Fuel Oil";
    case Lubricating_Oil:
        return "Lubricating Oil";
    case Bitumen:
        return "Bitumen";
    case Asphalt:
        return "Asphalt";
    case Rock:
        return "Rock";
    case Crushed_Rock:
        return "Crushed Rock";
    case Lime:
        return "Lime";
    
    default:
        return NULL;
    }
}

char* getState(const Product product) {
    switch (product)
    {
    case Iron_Ore:
        return "Solid";
    case Iron:
        return "Solid";
    case Coal:
        return "Solid";
    case Carbon:
        return "Solid";
    case Carbon_Monoxide:
        return "Gas";
    case Carbon_Dioxide:
        return "Gas";
    case Carbonic_Acid:
        return "Liquid";
    case Steel:
        return "Solid";
    case Copper_Ore:
        return "Solid";
    case Copper:
        return "Solid";
    case Copper_Wire:
        return "Solid";
    case Sand:
        return "Solid";
    case Silicon:
        return "Solid";
    case Water:
        return "Liquid";
    case Heavy_Water:
        return "Liquid";
    case Hydrogen:
        return "Gas";
    case Deuterium:
        return "Gas";
    case Oxygen:
        return "Gas";
    case Sulfur:
        return "Solid";
    case Sulfur_Dioxide:
        return "Gas";
    case Crude_Oil:
        return "Liquid";
    case Petroleum_Gas:
        return "Gas";
    case Gasoline:
        return "Liquid";
    case Naptha:
        return "Solid";
    case Plastic:
        return "Solid";
    case Kerosene:
        return "Liquid";
    case Aviation_Fuel:
        return "Liquid";
    case Diesel:
        return "Liquid";
    case Fuel_Oil:
        return "Liquid";
    case Lubricating_Oil:
        return "Liquid";
    case Bitumen:
        return "Solid";
    case Asphalt:
        return "Solid";
    case Rock:
        return "Solid";
    case Crushed_Rock:
        return "Solid";
    case Lime:
        return "Solid";
    
    default:
        return NULL;
    }
}

char* getShort(const Product product) {
    switch (product)
    {
    case Iron_Ore:
        return "Fe-";
    case Iron:
        return "Fe";
    case Coal:
        return "C-";
    case Carbon:
        return "C";
    case Carbon_Monoxide:
        return "CO";
    case Carbon_Dioxide:
        return "CO2";
    case Carbonic_Acid:
        return "H2CO3";
    case Steel:
        return "FeC";
    case Copper_Ore:
        return "Cu-";
    case Copper:
        return "Cu";
    case Copper_Wire:
        return "Wire";
    case Sand:
        return "SiO2";
    case Silicon:
        return "Si";
    case Water:
        return "H2O";
    case Heavy_Water:
        return "D2O";
    case Hydrogen:
        return "H";
    case Deuterium:
        return "D";
    case Oxygen:
        return "O";
    case Sulfur:
        return "S";
    case Sulfur_Dioxide:
        return "SO2";
    case Crude_Oil:
        return "Crude";
    case Petroleum_Gas:
        return "Petrol";
    case Gasoline:
        return "Gas";
    case Naptha:
        return "Nap";
    case Plastic:
        return "Plas";
    case Kerosene:
        return "Kero";
    case Aviation_Fuel:
        return "AvFu";
    case Diesel:
        return "Dsl";
    case Fuel_Oil:
        return "Fuel";
    case Lubricating_Oil:
        return "Lube";
    case Bitumen:
        return "Bitu";
    case Asphalt:
        return "Asph";
    case Rock:
        return "Rock";
    case Crushed_Rock:
        return "Crush";
    case Lime:
        return "Lime";
    
    default:
        return NULL;
    }
}

char* getCategory(const Product product) {
    switch (product)
    {
    case Iron_Ore:
        return "Raw";
    case Iron:
        return "Elemental";
    case Coal:
        return "Raw";
    case Carbon:
        return "Elemental";
    case Carbon_Monoxide:
        return "Molecule";
    case Carbon_Dioxide:
        return "Molecule";
    case Carbonic_Acid:
        return "Molecule";
    case Steel:
        return "Refined";
    case Copper_Ore:
        return "Raw";
    case Copper:
        return "Elemental";
    case Copper_Wire:
        return "Refined";
    case Sand:
        return "Raw";
    case Silicon:
        return "Elemental";
    case Water:
        return "Raw";
    case Heavy_Water:
        return "Raw";
    case Hydrogen:
        return "Elemental";
    case Deuterium:
        return "Elemental";
    case Oxygen:
        return "Elemental";
    case Sulfur:
        return "Elemental";
    case Sulfur_Dioxide:
        return "Molecule";
    case Crude_Oil:
        return "Raw";
    case Petroleum_Gas:
        return "Refined";
    case Gasoline:
        return "Refined";
    case Naptha:
        return "Refined";
    case Plastic:
        return "Intermediate";
    case Kerosene:
        return "Refined";
    case Aviation_Fuel:
        return "Fuel";
    case Diesel:
        return "Fuel";
    case Fuel_Oil:
        return "Refined";
    case Lubricating_Oil:
        return "Refined";
    case Bitumen:
        return "Refined";
    case Asphalt:
        return "Intermediate";
    case Rock:
        return "Raw";
    case Crushed_Rock:
        return "Refined";
    case Lime:
        return "Raw";
    
    default:
        return NULL;
    }
}

uint_fast16_t getGreenhouse(const Product product) {
    switch (product)
    {
    case Carbon_Monoxide:
        return +2;
    case Carbon_Dioxide:
        return +1;
    case Hydrogen:
        return +11;
    case Deuterium:
        return +11;
    case Oxygen:
        return +0;
    case Sulfur_Dioxide:
        return +0;
    
    default:
        return +0;
    }
}

float getAcidity(const Product product) {
    switch (product)
    {
    case Carbonic_Acid:
        return 4.68f;
    case Water:
        return 7.0f;
    case Heavy_Water:
        return 7.44f;
    case Crude_Oil:
        return 10.0f;
    
    default:
        return 0.0f;
    }
}

