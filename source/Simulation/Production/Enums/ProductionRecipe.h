#ifndef PRODUCTION_RECIPE_H
#define PRODUCTION_RECIPE_H

#include "..\Structures\Stockpile.h"

#include <stdint.h>
#include <stdlib.h>

typedef enum ProductionRecipe 
{
	Extraction_Iron_Ore,
	Extraction_Coal,
	Extraction_Copper_Ore,
	Extraction_Oxygen,
	Extraction_Hydrogen,
	Extraction_Water,
	Extraction_Heavy_Water,
	Extraction_Sand,
	Extraction_Sulfur,
	Extraction_Crude_Oil,
	Extraction_Rock,
	Extraction_Lime,
	Extraction_Nitrogen,
	Extraction_Timber,
	Extraction_Lithium_Carbonate,
	Extraction_Lime_Mineral,
	Extraction_Hydrogen_Peroxide,
	Extraction_Fluorite,
	Extraction_Table_Salt,
	Extraction_Phosphorite,
	Extraction_Wollastonite,
	Extraction_Bauxite,
	Refinement_Iron,
	Refinement_Copper,
	Refinement_Carbon,
	Refinement_Silicon,
	Crush_Rock,
	Fractional_Distillation,
	Refinement_Aviation_Fuel,
	Plastic_Production,
	Asphalt_Production,
	Steel_Production,
	Copper_Wire_Production,
	Electrolysis,
	Carbonic_Acid_Production,
	Combustion_Hydrogen,
	Combustion_Coal,
	Combustion_Carbon,
	Combustion_Sulfur,
	Combustion_Crude_Oil,
	Combustion_Petroleum_Gas,
	Combustion_Gasoline,
	Combustion_Kerosene,
	Combustion_Aviation_Fuel,
	Combustion_Diesel,
	Ammonia_Production,
	Nitric_Oxide_Production,
	Nitrogen_Dioxide_Production,
	Nitric_Acid_Production,
	Urea_Production,
	Fertiliser_Production_Synthetic,
	Wheat_Production,
	Flour_Production,
	Bread_Production,
	Lumber_Production,
	Furniture_Production,
	Paper_Production,
	Tissue_Production,
	Cotton_Production,
	Cotton_Fabric_Production,
	Apparel_Production,
	Tool_Production,
	Beef_Production,
	Fertiliser_Production_Manure,
	Graphite_Production,
	Calcium_Hydroxide_Production,
	Lithium_Hydroxide_Production,
	Lithium_Peroxide_Production,
	Lithium_Oxide_Production,
	Air_Purification_Lithium,
	Lithium_Battery_Production,
	Lithium_Hexafluorophosphate_Production,
	Hydrogen_Fluoride_Production,
	Lithium_Fluoride_Production,
	Carbonic_Acid_Decomposition,
	Phosphorus_Pentachloride_Production,
	Phosphorus_Trichloride_Production,
	Sulfuric_Acid_Production,
	Chlorine_Production,
	Phosphorus_Production,
	Sand_Refinement,
	Calcium_Production,
	Carbon_Monoxide_Shifting,
	Alumina_Refinement,
	Aluminum_Production,
	Population_Consumption,
	PRODUCTION_RECIPE_COUNT
} ProductionRecipe;

const char* getNameProductionRecipe(const ProductionRecipe productionRecipe);
const int_fast16_t getEnergy(const ProductionRecipe productionRecipe);
const uint_fast8_t getNumOfInputs(const ProductionRecipe productionRecipe);
const Stockpile* getInputs(const ProductionRecipe productionRecipe);
const uint_fast8_t getNumOfOutputs(const ProductionRecipe productionRecipe);
const Stockpile* getOutputs(const ProductionRecipe productionRecipe);
const QUANTITY_INT getCost(const ProductionRecipe productionRecipe, const Product product);
const QUANTITY_INT getResult(const ProductionRecipe productionRecipe, const Product product);


#endif