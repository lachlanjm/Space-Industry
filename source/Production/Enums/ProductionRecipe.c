#include "ProductionRecipe.h"

char* getName(const ProductionRecipe productionRecipe) {
    switch (productionRecipe)
    {
    case Extraction_Iron_Ore:
        return "Extraction Iron Ore";
    case Extraction_Coal:
        return "Extraction Coal";
    case Extraction_Copper_Ore:
        return "Extraction Copper Ore";
    case Extraction_Oxygen:
        return "Extraction Oxygen";
    case Extraction_Hydrogen:
        return "Extraction Hydrogen";
    case Extraction_Water:
        return "Extraction Water";
    case Extraction_Heavy_Water:
        return "Extraction Heavy Water";
    case Extraction_Sand:
        return "Extraction Sand";
    case Extraction_Sulfur:
        return "Extraction Sulfur";
    case Extraction_Crude_Oil:
        return "Extraction Crude Oil";
    case Extraction_Rock:
        return "Extraction Rock";
    case Extraction_Lime:
        return "Extraction Lime";
    case Refinement_Iron:
        return "Refinement Iron";
    case Refinement_Copper:
        return "Refinement Copper";
    case Refinement_Carbon:
        return "Refinement Carbon";
    case Refinement_Silicon:
        return "Refinement Silicon";
    case Crush_Rock:
        return "Crush Rock";
    case Fractional_Distillation:
        return "Fractional Distillation";
    case Refinement_Aviation_Fuel:
        return "Refinement Aviation Fuel";
    case Plastic_Production:
        return "Plastic Production";
    case Asphalt_Production:
        return "Asphalt Production";
    case Steel_Production:
        return "Steel Production";
    case Copper_Wire_Production:
        return "Copper Wire Production";
    case Electrolysis:
        return "Electrolysis";
    case Carbonic_Acid_Production:
        return "Carbonic Acid Production";
    case Combustion_Hydrogen:
        return "Combustion Hydrogen";
    case Combustion_Coal:
        return "Combustion Coal";
    case Combustion_Carbon:
        return "Combustion Carbon";
    case Combustion_Sulfur:
        return "Combustion Sulfur";
    case Combustion_Crude_Oil:
        return "Combustion Crude Oil";
    case Combustion_Petroleum_Gas:
        return "Combustion Petroleum Gas";
    case Combustion_Gasoline:
        return "Combustion Gasoline";
    case Combustion_Kerosene:
        return "Combustion Kerosene";
    case Combustion_Aviation_Fuel:
        return "Combustion Aviation Fuel";
    case Combustion_Diesel:
        return "Combustion Diesel";
    
    default:
        return NULL;
    }
}

int_fast16_t getEnergy(const ProductionRecipe productionRecipe) {
    switch (productionRecipe)
    {
    case Crush_Rock:
        return -1;
    case Fractional_Distillation:
        return -30;
    case Electrolysis:
        return -10;
    case Combustion_Hydrogen:
        return +10;
    case Combustion_Coal:
        return +200;
    case Combustion_Carbon:
        return +20;
    case Combustion_Sulfur:
        return +20;
    case Combustion_Crude_Oil:
        return +200;
    case Combustion_Petroleum_Gas:
        return +200;
    case Combustion_Gasoline:
        return +100;
    case Combustion_Kerosene:
        return +40;
    case Combustion_Aviation_Fuel:
        return +40;
    case Combustion_Diesel:
        return +40;
    
    default:
        return +0;
    }
}

uint_fast8_t getNumOfInputs(const ProductionRecipe productionRecipe) {
    switch (productionRecipe)
    {
    case Refinement_Iron:
        return 1;
    case Refinement_Copper:
        return 1;
    case Refinement_Carbon:
        return 2;
    case Refinement_Silicon:
        return 2;
    case Crush_Rock:
        return 1;
    case Fractional_Distillation:
        return 1;
    case Refinement_Aviation_Fuel:
        return 1;
    case Plastic_Production:
        return 1;
    case Asphalt_Production:
        return 4;
    case Steel_Production:
        return 2;
    case Copper_Wire_Production:
        return 1;
    case Electrolysis:
        return 1;
    case Carbonic_Acid_Production:
        return 2;
    case Combustion_Hydrogen:
        return 2;
    case Combustion_Coal:
        return 2;
    case Combustion_Carbon:
        return 2;
    case Combustion_Sulfur:
        return 2;
    case Combustion_Crude_Oil:
        return 2;
    case Combustion_Petroleum_Gas:
        return 2;
    case Combustion_Gasoline:
        return 2;
    case Combustion_Kerosene:
        return 2;
    case Combustion_Aviation_Fuel:
        return 2;
    case Combustion_Diesel:
        return 2;
    
    default:
        return 0;
    }
}

Stockpile* getInputs(const ProductionRecipe productionRecipe) {
    switch (productionRecipe)
    {
    case Refinement_Iron:
        static const Stockpile ___Refinement_Iron___inputs_static[] = {{Iron_Ore, 1}};
        return ___Refinement_Iron___inputs_static;
    case Refinement_Copper:
        static const Stockpile ___Refinement_Copper___inputs_static[] = {{Copper_Ore, 1}};
        return ___Refinement_Copper___inputs_static;
    case Refinement_Carbon:
        static const Stockpile ___Refinement_Carbon___inputs_static[] = {{Coal, 10}, {Oxygen, 2}};
        return ___Refinement_Carbon___inputs_static;
    case Refinement_Silicon:
        static const Stockpile ___Refinement_Silicon___inputs_static[] = {{Sand, 1}, {Carbon, 2}};
        return ___Refinement_Silicon___inputs_static;
    case Crush_Rock:
        static const Stockpile ___Crush_Rock___inputs_static[] = {{Rock, 2}};
        return ___Crush_Rock___inputs_static;
    case Fractional_Distillation:
        static const Stockpile ___Fractional_Distillation___inputs_static[] = {{Crude_Oil, 100}};
        return ___Fractional_Distillation___inputs_static;
    case Refinement_Aviation_Fuel:
        static const Stockpile ___Refinement_Aviation_Fuel___inputs_static[] = {{Kerosene, 1}};
        return ___Refinement_Aviation_Fuel___inputs_static;
    case Plastic_Production:
        static const Stockpile ___Plastic_Production___inputs_static[] = {{Naptha, 1}};
        return ___Plastic_Production___inputs_static;
    case Asphalt_Production:
        static const Stockpile ___Asphalt_Production___inputs_static[] = {{Crushed_Rock, 5}, {Sand, 5}, {Lime, 5}, {Bitumen, 1}};
        return ___Asphalt_Production___inputs_static;
    case Steel_Production:
        static const Stockpile ___Steel_Production___inputs_static[] = {{Iron, 49}, {Carbon, 1}};
        return ___Steel_Production___inputs_static;
    case Copper_Wire_Production:
        static const Stockpile ___Copper_Wire_Production___inputs_static[] = {{Copper, 1}};
        return ___Copper_Wire_Production___inputs_static;
    case Electrolysis:
        static const Stockpile ___Electrolysis___inputs_static[] = {{Water, 1}};
        return ___Electrolysis___inputs_static;
    case Carbonic_Acid_Production:
        static const Stockpile ___Carbonic_Acid_Production___inputs_static[] = {{Water, 1}, {Carbon_Dioxide, 1}};
        return ___Carbonic_Acid_Production___inputs_static;
    case Combustion_Hydrogen:
        static const Stockpile ___Combustion_Hydrogen___inputs_static[] = {{Hydrogen, 2}, {Oxygen, 1}};
        return ___Combustion_Hydrogen___inputs_static;
    case Combustion_Coal:
        static const Stockpile ___Combustion_Coal___inputs_static[] = {{Coal, 10}, {Oxygen, 20}};
        return ___Combustion_Coal___inputs_static;
    case Combustion_Carbon:
        static const Stockpile ___Combustion_Carbon___inputs_static[] = {{Carbon, 1}, {Oxygen, 2}};
        return ___Combustion_Carbon___inputs_static;
    case Combustion_Sulfur:
        static const Stockpile ___Combustion_Sulfur___inputs_static[] = {{Sulfur, 1}, {Oxygen, 2}};
        return ___Combustion_Sulfur___inputs_static;
    case Combustion_Crude_Oil:
        static const Stockpile ___Combustion_Crude_Oil___inputs_static[] = {{Crude_Oil, 10}, {Oxygen, 41}};
        return ___Combustion_Crude_Oil___inputs_static;
    case Combustion_Petroleum_Gas:
        static const Stockpile ___Combustion_Petroleum_Gas___inputs_static[] = {{Petroleum_Gas, 10}, {Oxygen, 13}};
        return ___Combustion_Petroleum_Gas___inputs_static;
    case Combustion_Gasoline:
        static const Stockpile ___Combustion_Gasoline___inputs_static[] = {{Gasoline, 5}, {Oxygen, 50}};
        return ___Combustion_Gasoline___inputs_static;
    case Combustion_Kerosene:
        static const Stockpile ___Combustion_Kerosene___inputs_static[] = {{Kerosene, 2}, {Oxygen, 54}};
        return ___Combustion_Kerosene___inputs_static;
    case Combustion_Aviation_Fuel:
        static const Stockpile ___Combustion_Aviation_Fuel___inputs_static[] = {{Aviation_Fuel, 2}, {Oxygen, 50}};
        return ___Combustion_Aviation_Fuel___inputs_static;
    case Combustion_Diesel:
        static const Stockpile ___Combustion_Diesel___inputs_static[] = {{Diesel, 2}, {Oxygen, 72}};
        return ___Combustion_Diesel___inputs_static;
    
    default:
        return NULL;
    }
}

uint_fast8_t getNumOfOutputs(const ProductionRecipe productionRecipe) {
    switch (productionRecipe)
    {
    case Extraction_Iron_Ore:
        return 1;
    case Extraction_Coal:
        return 1;
    case Extraction_Copper_Ore:
        return 1;
    case Extraction_Oxygen:
        return 1;
    case Extraction_Hydrogen:
        return 1;
    case Extraction_Water:
        return 1;
    case Extraction_Heavy_Water:
        return 1;
    case Extraction_Sand:
        return 1;
    case Extraction_Sulfur:
        return 1;
    case Extraction_Crude_Oil:
        return 1;
    case Extraction_Rock:
        return 1;
    case Extraction_Lime:
        return 1;
    case Refinement_Iron:
        return 1;
    case Refinement_Copper:
        return 1;
    case Refinement_Carbon:
        return 2;
    case Refinement_Silicon:
        return 2;
    case Crush_Rock:
        return 1;
    case Fractional_Distillation:
        return 9;
    case Refinement_Aviation_Fuel:
        return 1;
    case Plastic_Production:
        return 1;
    case Asphalt_Production:
        return 1;
    case Steel_Production:
        return 1;
    case Copper_Wire_Production:
        return 1;
    case Electrolysis:
        return 2;
    case Carbonic_Acid_Production:
        return 1;
    case Combustion_Hydrogen:
        return 1;
    case Combustion_Coal:
        return 2;
    case Combustion_Carbon:
        return 1;
    case Combustion_Sulfur:
        return 1;
    case Combustion_Crude_Oil:
        return 4;
    case Combustion_Petroleum_Gas:
        return 2;
    case Combustion_Gasoline:
        return 2;
    case Combustion_Kerosene:
        return 2;
    case Combustion_Aviation_Fuel:
        return 2;
    case Combustion_Diesel:
        return 2;
    
    default:
        return 0;
    }
}

Stockpile* getOutputs(const ProductionRecipe productionRecipe) {
    switch (productionRecipe)
    {
    case Extraction_Iron_Ore:
        static const Stockpile ___Extraction_Iron_Ore___outputs_static[] = {{Iron_Ore, 1}};
        return ___Extraction_Iron_Ore___outputs_static;
    case Extraction_Coal:
        static const Stockpile ___Extraction_Coal___outputs_static[] = {{Coal, 1}};
        return ___Extraction_Coal___outputs_static;
    case Extraction_Copper_Ore:
        static const Stockpile ___Extraction_Copper_Ore___outputs_static[] = {{Copper_Ore, 1}};
        return ___Extraction_Copper_Ore___outputs_static;
    case Extraction_Oxygen:
        static const Stockpile ___Extraction_Oxygen___outputs_static[] = {{Oxygen, 1}};
        return ___Extraction_Oxygen___outputs_static;
    case Extraction_Hydrogen:
        static const Stockpile ___Extraction_Hydrogen___outputs_static[] = {{Hydrogen, 1}};
        return ___Extraction_Hydrogen___outputs_static;
    case Extraction_Water:
        static const Stockpile ___Extraction_Water___outputs_static[] = {{Water, 1}};
        return ___Extraction_Water___outputs_static;
    case Extraction_Heavy_Water:
        static const Stockpile ___Extraction_Heavy_Water___outputs_static[] = {{Heavy_Water, 1}};
        return ___Extraction_Heavy_Water___outputs_static;
    case Extraction_Sand:
        static const Stockpile ___Extraction_Sand___outputs_static[] = {{Sand, 1}};
        return ___Extraction_Sand___outputs_static;
    case Extraction_Sulfur:
        static const Stockpile ___Extraction_Sulfur___outputs_static[] = {{Sulfur, 1}};
        return ___Extraction_Sulfur___outputs_static;
    case Extraction_Crude_Oil:
        static const Stockpile ___Extraction_Crude_Oil___outputs_static[] = {{Crude_Oil, 1}};
        return ___Extraction_Crude_Oil___outputs_static;
    case Extraction_Rock:
        static const Stockpile ___Extraction_Rock___outputs_static[] = {{Rock, 1}};
        return ___Extraction_Rock___outputs_static;
    case Extraction_Lime:
        static const Stockpile ___Extraction_Lime___outputs_static[] = {{Lime, 1}};
        return ___Extraction_Lime___outputs_static;
    case Refinement_Iron:
        static const Stockpile ___Refinement_Iron___outputs_static[] = {{Iron, 1}};
        return ___Refinement_Iron___outputs_static;
    case Refinement_Copper:
        static const Stockpile ___Refinement_Copper___outputs_static[] = {{Copper, 1}};
        return ___Refinement_Copper___outputs_static;
    case Refinement_Carbon:
        static const Stockpile ___Refinement_Carbon___outputs_static[] = {{Carbon, 9}, {Sulfur_Dioxide, 1}};
        return ___Refinement_Carbon___outputs_static;
    case Refinement_Silicon:
        static const Stockpile ___Refinement_Silicon___outputs_static[] = {{Silicon, 1}, {Carbon_Monoxide, 2}};
        return ___Refinement_Silicon___outputs_static;
    case Crush_Rock:
        static const Stockpile ___Crush_Rock___outputs_static[] = {{Crushed_Rock, 2}};
        return ___Crush_Rock___outputs_static;
    case Fractional_Distillation:
        static const Stockpile ___Fractional_Distillation___outputs_static[] = {{Petroleum_Gas, 4}, {Gasoline, 46}, {Naptha, 2}, {Kerosene, 11}, {Diesel, 30}, {Fuel_Oil, 2}, {Lubricating_Oil, 1}, {Bitumen, 2}, {Carbon, 5}};
        return ___Fractional_Distillation___outputs_static;
    case Refinement_Aviation_Fuel:
        static const Stockpile ___Refinement_Aviation_Fuel___outputs_static[] = {{Aviation_Fuel, 1}};
        return ___Refinement_Aviation_Fuel___outputs_static;
    case Plastic_Production:
        static const Stockpile ___Plastic_Production___outputs_static[] = {{Plastic, 1}};
        return ___Plastic_Production___outputs_static;
    case Asphalt_Production:
        static const Stockpile ___Asphalt_Production___outputs_static[] = {{Asphalt, 15}};
        return ___Asphalt_Production___outputs_static;
    case Steel_Production:
        static const Stockpile ___Steel_Production___outputs_static[] = {{Steel, 50}};
        return ___Steel_Production___outputs_static;
    case Copper_Wire_Production:
        static const Stockpile ___Copper_Wire_Production___outputs_static[] = {{Copper_Wire, 1}};
        return ___Copper_Wire_Production___outputs_static;
    case Electrolysis:
        static const Stockpile ___Electrolysis___outputs_static[] = {{Hydrogen, 2}, {Oxygen, 1}};
        return ___Electrolysis___outputs_static;
    case Carbonic_Acid_Production:
        static const Stockpile ___Carbonic_Acid_Production___outputs_static[] = {{Carbonic_Acid, 1}};
        return ___Carbonic_Acid_Production___outputs_static;
    case Combustion_Hydrogen:
        static const Stockpile ___Combustion_Hydrogen___outputs_static[] = {{Water, 1}};
        return ___Combustion_Hydrogen___outputs_static;
    case Combustion_Coal:
        static const Stockpile ___Combustion_Coal___outputs_static[] = {{Carbon_Dioxide, 9}, {Sulfur_Dioxide, 1}};
        return ___Combustion_Coal___outputs_static;
    case Combustion_Carbon:
        static const Stockpile ___Combustion_Carbon___outputs_static[] = {{Carbon_Dioxide, 1}};
        return ___Combustion_Carbon___outputs_static;
    case Combustion_Sulfur:
        static const Stockpile ___Combustion_Sulfur___outputs_static[] = {{Sulfur_Dioxide, 1}};
        return ___Combustion_Sulfur___outputs_static;
    case Combustion_Crude_Oil:
        static const Stockpile ___Combustion_Crude_Oil___outputs_static[] = {{Carbon_Dioxide, 9}, {Water, 7}, {Nitrogen_Dioxide, 2}, {Sulfur_Dioxide, 6}};
        return ___Combustion_Crude_Oil___outputs_static;
    case Combustion_Petroleum_Gas:
        static const Stockpile ___Combustion_Petroleum_Gas___outputs_static[] = {{Carbon_Dioxide, 4}, {Water, 5}};
        return ___Combustion_Petroleum_Gas___outputs_static;
    case Combustion_Gasoline:
        static const Stockpile ___Combustion_Gasoline___outputs_static[] = {{Carbon_Dioxide, 16}, {Water, 18}};
        return ___Combustion_Gasoline___outputs_static;
    case Combustion_Kerosene:
        static const Stockpile ___Combustion_Kerosene___outputs_static[] = {{Carbon_Dioxide, 24}, {Water, 26}};
        return ___Combustion_Kerosene___outputs_static;
    case Combustion_Aviation_Fuel:
        static const Stockpile ___Combustion_Aviation_Fuel___outputs_static[] = {{Carbon_Dioxide, 16}, {Water, 18}};
        return ___Combustion_Aviation_Fuel___outputs_static;
    case Combustion_Diesel:
        static const Stockpile ___Combustion_Diesel___outputs_static[] = {{Carbon_Dioxide, 24}, {Water, 24}};
        return ___Combustion_Diesel___outputs_static;
    
    default:
        return NULL;
    }
}

QUANTITY_INT getCost(const ProductionRecipe productionRecipe, const Product product) {
    switch (productionRecipe)
    {
    case Refinement_Iron:
        switch (product) {
        case Iron_Ore:
            return 1;
        
        default:
            return 0;
        }
    case Refinement_Copper:
        switch (product) {
        case Copper_Ore:
            return 1;
        
        default:
            return 0;
        }
    case Refinement_Carbon:
        switch (product) {
        case Coal:
            return 10;
        case Oxygen:
            return 2;
        
        default:
            return 0;
        }
    case Refinement_Silicon:
        switch (product) {
        case Sand:
            return 1;
        case Carbon:
            return 2;
        
        default:
            return 0;
        }
    case Crush_Rock:
        switch (product) {
        case Rock:
            return 2;
        
        default:
            return 0;
        }
    case Fractional_Distillation:
        switch (product) {
        case Crude_Oil:
            return 100;
        
        default:
            return 0;
        }
    case Refinement_Aviation_Fuel:
        switch (product) {
        case Kerosene:
            return 1;
        
        default:
            return 0;
        }
    case Plastic_Production:
        switch (product) {
        case Naptha:
            return 1;
        
        default:
            return 0;
        }
    case Asphalt_Production:
        switch (product) {
        case Crushed_Rock:
            return 5;
        case Sand:
            return 5;
        case Lime:
            return 5;
        case Bitumen:
            return 1;
        
        default:
            return 0;
        }
    case Steel_Production:
        switch (product) {
        case Iron:
            return 49;
        case Carbon:
            return 1;
        
        default:
            return 0;
        }
    case Copper_Wire_Production:
        switch (product) {
        case Copper:
            return 1;
        
        default:
            return 0;
        }
    case Electrolysis:
        switch (product) {
        case Water:
            return 1;
        
        default:
            return 0;
        }
    case Carbonic_Acid_Production:
        switch (product) {
        case Water:
            return 1;
        case Carbon_Dioxide:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Hydrogen:
        switch (product) {
        case Hydrogen:
            return 2;
        case Oxygen:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Coal:
        switch (product) {
        case Coal:
            return 10;
        case Oxygen:
            return 20;
        
        default:
            return 0;
        }
    case Combustion_Carbon:
        switch (product) {
        case Carbon:
            return 1;
        case Oxygen:
            return 2;
        
        default:
            return 0;
        }
    case Combustion_Sulfur:
        switch (product) {
        case Sulfur:
            return 1;
        case Oxygen:
            return 2;
        
        default:
            return 0;
        }
    case Combustion_Crude_Oil:
        switch (product) {
        case Crude_Oil:
            return 10;
        case Oxygen:
            return 41;
        
        default:
            return 0;
        }
    case Combustion_Petroleum_Gas:
        switch (product) {
        case Petroleum_Gas:
            return 10;
        case Oxygen:
            return 13;
        
        default:
            return 0;
        }
    case Combustion_Gasoline:
        switch (product) {
        case Gasoline:
            return 5;
        case Oxygen:
            return 50;
        
        default:
            return 0;
        }
    case Combustion_Kerosene:
        switch (product) {
        case Kerosene:
            return 2;
        case Oxygen:
            return 54;
        
        default:
            return 0;
        }
    case Combustion_Aviation_Fuel:
        switch (product) {
        case Aviation_Fuel:
            return 2;
        case Oxygen:
            return 50;
        
        default:
            return 0;
        }
    case Combustion_Diesel:
        switch (product) {
        case Diesel:
            return 2;
        case Oxygen:
            return 72;
        
        default:
            return 0;
        }
    
    default:
        return 0;
    }
}

QUANTITY_INT getResult(const ProductionRecipe productionRecipe, const Product product) {
    switch (productionRecipe)
    {
    case Extraction_Iron_Ore:
        switch (product) {
        case Iron_Ore:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Coal:
        switch (product) {
        case Coal:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Copper_Ore:
        switch (product) {
        case Copper_Ore:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Oxygen:
        switch (product) {
        case Oxygen:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Hydrogen:
        switch (product) {
        case Hydrogen:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Water:
        switch (product) {
        case Water:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Heavy_Water:
        switch (product) {
        case Heavy_Water:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Sand:
        switch (product) {
        case Sand:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Sulfur:
        switch (product) {
        case Sulfur:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Crude_Oil:
        switch (product) {
        case Crude_Oil:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Rock:
        switch (product) {
        case Rock:
            return 1;
        
        default:
            return 0;
        }
    case Extraction_Lime:
        switch (product) {
        case Lime:
            return 1;
        
        default:
            return 0;
        }
    case Refinement_Iron:
        switch (product) {
        case Iron:
            return 1;
        
        default:
            return 0;
        }
    case Refinement_Copper:
        switch (product) {
        case Copper:
            return 1;
        
        default:
            return 0;
        }
    case Refinement_Carbon:
        switch (product) {
        case Carbon:
            return 9;
        case Sulfur_Dioxide:
            return 1;
        
        default:
            return 0;
        }
    case Refinement_Silicon:
        switch (product) {
        case Silicon:
            return 1;
        case Carbon_Monoxide:
            return 2;
        
        default:
            return 0;
        }
    case Crush_Rock:
        switch (product) {
        case Crushed_Rock:
            return 2;
        
        default:
            return 0;
        }
    case Fractional_Distillation:
        switch (product) {
        case Petroleum_Gas:
            return 4;
        case Gasoline:
            return 46;
        case Naptha:
            return 2;
        case Kerosene:
            return 11;
        case Diesel:
            return 30;
        case Fuel_Oil:
            return 2;
        case Lubricating_Oil:
            return 1;
        case Bitumen:
            return 2;
        case Carbon:
            return 5;
        
        default:
            return 0;
        }
    case Refinement_Aviation_Fuel:
        switch (product) {
        case Aviation_Fuel:
            return 1;
        
        default:
            return 0;
        }
    case Plastic_Production:
        switch (product) {
        case Plastic:
            return 1;
        
        default:
            return 0;
        }
    case Asphalt_Production:
        switch (product) {
        case Asphalt:
            return 15;
        
        default:
            return 0;
        }
    case Steel_Production:
        switch (product) {
        case Steel:
            return 50;
        
        default:
            return 0;
        }
    case Copper_Wire_Production:
        switch (product) {
        case Copper_Wire:
            return 1;
        
        default:
            return 0;
        }
    case Electrolysis:
        switch (product) {
        case Hydrogen:
            return 2;
        case Oxygen:
            return 1;
        
        default:
            return 0;
        }
    case Carbonic_Acid_Production:
        switch (product) {
        case Carbonic_Acid:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Hydrogen:
        switch (product) {
        case Water:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Coal:
        switch (product) {
        case Carbon_Dioxide:
            return 9;
        case Sulfur_Dioxide:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Carbon:
        switch (product) {
        case Carbon_Dioxide:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Sulfur:
        switch (product) {
        case Sulfur_Dioxide:
            return 1;
        
        default:
            return 0;
        }
    case Combustion_Crude_Oil:
        switch (product) {
        case Carbon_Dioxide:
            return 9;
        case Water:
            return 7;
        case Nitrogen_Dioxide:
            return 2;
        case Sulfur_Dioxide:
            return 6;
        
        default:
            return 0;
        }
    case Combustion_Petroleum_Gas:
        switch (product) {
        case Carbon_Dioxide:
            return 4;
        case Water:
            return 5;
        
        default:
            return 0;
        }
    case Combustion_Gasoline:
        switch (product) {
        case Carbon_Dioxide:
            return 16;
        case Water:
            return 18;
        
        default:
            return 0;
        }
    case Combustion_Kerosene:
        switch (product) {
        case Carbon_Dioxide:
            return 24;
        case Water:
            return 26;
        
        default:
            return 0;
        }
    case Combustion_Aviation_Fuel:
        switch (product) {
        case Carbon_Dioxide:
            return 16;
        case Water:
            return 18;
        
        default:
            return 0;
        }
    case Combustion_Diesel:
        switch (product) {
        case Carbon_Dioxide:
            return 24;
        case Water:
            return 24;
        
        default:
            return 0;
        }
    
    default:
        return 0;
    }
}

