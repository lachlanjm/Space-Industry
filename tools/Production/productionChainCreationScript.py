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
    {0}
}} ProductionRecipe;

{1}

#endif"""

    product_c_start = """#include "ProductionRecipe.h"

"""

    class Recipe:
        def __init__(self, name) -> None:
            self.name = name
            self.energy = None
            self.inputs = []
            self.outputs = []
        
        def __str__(self) -> str:
            return self.name

        def addEnergy(self, energy):
            self.energy = energy
        
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

    case_format = """case {0}:
        return {1};
    """

    case_static_format = """case {0}:
        static const Stockpile ___{0}___{1}_static[] = {{{2}}};
        return ___{0}___{1}_static;
    """

    stock_arr_format = "{{{0}, {1}}}"

    case_recur_format = """case {0}:
        switch (product) {{
        {2}
        default:
            return {1};
        }}
    """

    case_base_format = """case {0}:
            return {1};
        """

    ### Start of program
    recipes = []
    recipe_funcs = [
        "char* getName(const ProductionRecipe productionRecipe)", 
        "int_fast16_t getEnergy(const ProductionRecipe productionRecipe)", 
        "uint_fast8_t getNumOfInputs(const ProductionRecipe productionRecipe)",
        "Stockpile* getInputs(const ProductionRecipe productionRecipe)",
        "uint_fast8_t getNumOfOutputs(const ProductionRecipe productionRecipe)",
        "Stockpile* getOutputs(const ProductionRecipe productionRecipe)",
        "QUANTITY_INT getCost(const ProductionRecipe productionRecipe, const Product product)",
        "QUANTITY_INT getResult(const ProductionRecipe productionRecipe, const Product product)"
    ]
    case_groups = ["", "", "", "", "", "", "", ""]
    def_vals = ["NULL", "+0", "0", "NULL", "0", "NULL", "0", "0"]

    with open(os.path.join(os.path.dirname(__file__), "ProductionChains.in"), "r") as f:
        line = f.readline()

        inps = False
        outs = False

        while line:
            if line == "\n":
                case_groups[0] += case_format.format(recipes[-1], '"' + recipes[-1].name.replace("_", " ") + '"')
                if recipes[-1].energy is not None:
                    case_groups[1] += case_format.format(recipes[-1], recipes[-1].energy)

                if len(recipes[-1].inputs):
                    case_groups[2] += case_format.format(recipes[-1], len(recipes[-1].inputs))
                    case_groups[3] += case_static_format.format(recipes[-1], "inputs", ", ".join(
                        stock_arr_format.format(x[1], x[0])
                        for x in recipes[-1].inputs
                    ))
                    case_groups[6] += case_recur_format.format(recipes[-1], "0",
                        "".join(case_base_format.format(x[1], x[0]) for x in recipes[-1].inputs)
                    )
                if len(recipes[-1].outputs):
                    case_groups[4] += case_format.format(recipes[-1], len(recipes[-1].outputs))
                    case_groups[5] += case_static_format.format(recipes[-1], "outputs", ", ".join(
                        stock_arr_format.format(x[1], x[0])
                        for x in recipes[-1].outputs
                    ))
                    case_groups[7] += case_recur_format.format(recipes[-1], "0",
                        "".join(case_base_format.format(x[1], x[0]) for x in recipes[-1].outputs)
                    )

                inps = False
                outs = False

            elif line[0] == "\t" or line[0] == " ":
                if line.strip().startswith("Energy:"):
                    value = line[line.index(":")+2:].strip()
                    recipes[-1].addEnergy(value)
                
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

    with open(os.path.join(os.path.dirname(__file__), "..\..\source\Production\Enums\ProductionRecipe.h"), "w") as f:
        recipes_names = [p.name for p in recipes]
        f.write(product_h_format.format(
            ",\n\t".join(recipes_names),
            ";\n".join(recipe_funcs) + ";\n"
        ))

    with open(os.path.join(os.path.dirname(__file__), "..\..\source\Production\Enums\ProductionRecipe.c"), "w") as f:
        f.write(product_c_start)

        for i in range(len(recipe_funcs)):
            f.write(function_format.format(recipe_funcs[i], case_groups[i], def_vals[i]))




if __name__ == "__main__":
    main()
