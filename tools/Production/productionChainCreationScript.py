import os

#### TODO FIX TO MAKE ARRAY-BASED INFO RETRIEVAL
def main():
	product_h_format = """#ifndef PRODUCTION_RECIPE_H
#define PRODUCTION_RECIPE_H

#include "..\Structures\Stockpile.h"

#include <stdint.h>
#include <stdlib.h>

typedef enum ProductionRecipe 
{{
	{0},
	PRODUCTION_RECIPE_COUNT
}} ProductionRecipe;

{1}

#endif"""

	product_c_start = """#include "ProductionRecipe.h"

"""

	class Recipe:
		def __init__(self, name) -> None:
			self.name = name
			self.energy = None
			self.baseProcessingSpeed = None
			self.inputs = []
			self.outputs = []
		
		def __str__(self) -> str:
			return self.name

		def addEnergy(self, energy):
			self.energy = energy

		def addBaseProcessingSpeed(self, speed):
			self.baseProcessingSpeed = speed
		
		def addInputs(self, inputs):
			self.inputs.append(inputs)

		def addOutputs(self, outputs):
			self.outputs.append(outputs)

	function_format = """{0} {{
	switch (productionRecipe)
	{{
	{1}
	default:
		return {2};
	}}
}}

"""

	stock_arr_format = "{{{0}, {1}}}"
	
	function_format_arr = """const static {1} {2}[] =
{{{3}
}};
const {0} {{
	return {2}[productionRecipe];
}}

"""

	function_format_arr_ext = """const static {1}* {2}[] =
{{{3}
}};
const {0} {{
	return {2}[productionRecipe][product];
}}

"""

	### Start of program
	products = []
	recipes = []
	data_types = ["char*", "int_fast16_t", "uint_fast8_t", "Stockpile*", "uint_fast8_t", "Stockpile*", "QUANTITY_INT", "QUANTITY_INT", "uint_fast16_t"]
	recipe_funcs = [
		f"{data_types[0]} getNameProductionRecipe(const ProductionRecipe productionRecipe)", 
		f"{data_types[1]} getEnergy(const ProductionRecipe productionRecipe)", 
		f"{data_types[2]} getNumOfInputs(const ProductionRecipe productionRecipe)",
		f"{data_types[3]} getInputs(const ProductionRecipe productionRecipe)",
		f"{data_types[4]} getNumOfOutputs(const ProductionRecipe productionRecipe)",
		f"{data_types[5]} getOutputs(const ProductionRecipe productionRecipe)",
		f"{data_types[6]} getCost(const ProductionRecipe productionRecipe, const Product product)",
		f"{data_types[7]} getResult(const ProductionRecipe productionRecipe, const Product product)",
		f"{data_types[8]} getBaseProcessingSpeed(const ProductionRecipe productionRecipe)"
	]
	arr_groups = ["", "", "", "", "", "", "", "", ""]
	arr_names = ["__production_recipe_name_arr", "__production_recipe_energy_arr", "__production_recipe_num_inputs_arr", "__production_recipe_inputs_arr", "__production_recipe_num_outputs_arr", "__production_recipe_outputs_arr", "__production_recipe_costs_arr", "__production_recipe_results_arr", "__production_recipe_base_proc_speed_arr"]
	def_vals = ["NULL", "+0", "0", "NULL", "0", "NULL", "0", "0", "1"]

	with open(os.path.join(os.path.dirname(__file__), "Products.in"), "r") as f:
		line = f.readline()

		while line:
			if line == "\n" or line[0] == "\t" or line[0] == " ":
				pass
			else:
				products.append(line.strip().replace(" ", "_"))
			
			line = f.readline()

	with open(os.path.join(os.path.dirname(__file__), "ProductionChains.in"), "r") as f:
		line = f.readline()

		inps = False
		outs = False

		while line:
			if line == "\n":
				arr_groups[0] += '\n\t"' + recipes[-1].name.replace("_", " ") + '", '

				if recipes[-1].energy is None:
					arr_groups[1] += '\n\t' + def_vals[1] + ', '
				else:
					arr_groups[1] += '\n\t' + recipes[-1].energy + ', '
				
				if recipes[-1].baseProcessingSpeed is None:
					arr_groups[8] += '\n\t' + def_vals[8] + ', '
				else:
					arr_groups[8] += '\n\t' + recipes[-1].baseProcessingSpeed + ', '

				if len(recipes[-1].inputs):
					arr_groups[2] += '\n\t' + str(len(recipes[-1].inputs)) + ', '
					arr_groups[3] += f'\n\t(Stockpile[]) {{' + ", ".join(stock_arr_format.format(x[1], x[0]) for x in recipes[-1].inputs) + '}, '
				else:
					arr_groups[2] += '\n\t' + def_vals[2] + ', '
					arr_groups[3] += '\n\t' + def_vals[3] + ', '
				
				arr_groups[6] += f'\n\t({data_types[6]}[]) {{'
				for prod in products:
					value = 0
					for inp in recipes[-1].inputs:
						if inp[1] == prod:
							value = inp[0]
					arr_groups[6] += str(value) + ', '
				arr_groups[6] = arr_groups[6][:-2] + '}, '
				
				if len(recipes[-1].outputs):
					arr_groups[4] += '\n\t' + str(len(recipes[-1].outputs)) + ', '
					arr_groups[5] += f'\n\t(Stockpile[]) {{' + ", ".join(stock_arr_format.format(x[1], x[0]) for x in recipes[-1].outputs) + '}, '
				else:
					arr_groups[4] += '\n\t' + def_vals[4] + ', '
					arr_groups[5] += '\n\t' + def_vals[5] + ', '

				arr_groups[7] += f'\n\t({data_types[7]}[]) {{'
				for prod in products:
					value = 0
					for out in recipes[-1].outputs:
						if out[1] == prod:
							value = out[0]
					arr_groups[7] += str(value) + ', '
				arr_groups[7] = arr_groups[7][:-2] + '}, '

				inps = False
				outs = False

			elif line[0] == "\t" or line[0] == " ":
				if line.strip().startswith("Energy:"):
					value = line[line.index(":")+2:].strip()
					recipes[-1].addEnergy(value)
				elif line.strip().startswith("Processing speed:"):
					value = line[line.index(":")+2:].strip()
					recipes[-1].addBaseProcessingSpeed(value)
				
				elif line.strip().startswith("Input:"):
					inps = True
					outs = False
				elif line.strip().startswith("Output:"):
					inps = False
					outs = True
				
				elif inps:
					quant = line[:line.index("x")].strip()
					product = line[line.index("x")+2:].strip().replace(" ", "_")
					recipes[-1].addInputs((quant, product))
				elif outs:
					quant = line[:line.index("x")].strip()
					product = line[line.index("x")+2:].strip().replace(" ", "_")
					recipes[-1].addOutputs((quant, product))
				
			else:
				recipes.append(Recipe(line.strip().replace(" ", "_")))
			
			line = f.readline()

	with open(os.path.join(os.path.dirname(__file__), "..\..\source\Simulation\Production\Enums\ProductionRecipe.h"), "w") as f:
		recipes_names = [p.name for p in recipes]
		f.write(product_h_format.format(
			",\n\t".join(recipes_names),
			"const " + ";\nconst ".join(recipe_funcs) + ";\n"
		))

	with open(os.path.join(os.path.dirname(__file__), "..\..\source\Simulation\Production\Enums\ProductionRecipe.c"), "w") as f:
		f.write(product_c_start)

		for i in range(6):
			f.write(function_format_arr.format(recipe_funcs[i], data_types[i], arr_names[i], arr_groups[i]))
		
		f.write(function_format_arr_ext.format(recipe_funcs[6], data_types[6], arr_names[6], arr_groups[6]))
		f.write(function_format_arr_ext.format(recipe_funcs[7], data_types[7], arr_names[7], arr_groups[7]))

		f.write(function_format_arr.format(recipe_funcs[8], data_types[8], arr_names[8], arr_groups[8]))



if __name__ == "__main__":
	main()
