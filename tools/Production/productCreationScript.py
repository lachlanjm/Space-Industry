import os

def main():
    product_h_format = """#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdint.h>
#include <stdlib.h>

typedef enum Product 
{{
    {0}
}} Product;

{1}

#endif"""

    product_c_start = """#include "Product.h"

"""

    class Product:
        def __init__(self, name) -> None:
            self.name = name
            self.state = None
            self.short = None
            self.category = None
            self.greenhouse = None
            self.acidity = None
        
        def __str__(self) -> str:
            return self.name

        def addState(self, state):
            self.state = state
        
        def addShort(self, short):
            self.short = short

        def addCategory(self, category):
            self.category = category

        def addGreenhouseEffect(self, effect):
            self.greenhouse = effect

        def addAcidity(self, acidity):
            self.acidity = acidity

    function_format = """{0} {{
    switch (product)
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

    function_format_arr = """const static {1} {2}[] =
{{
{3}
}};
{0} {{
    return {2}[product];
}}

"""

    ### Start of program
    products = []
    product_funcs = [
        "char* getName(const Product product)", 
        "char* getState(const Product product)", 
        "char* getShort(const Product product)", 
        "char* getCategory(const Product product)", 
        "uint_fast16_t getGreenhouse(const Product product)", 
        "float getAcidity(const Product product)"
    ]
    data_types = ["char*", "char*", "char*", "char*", "uint_fast16_t", "float"]
    arr_names = ["__product_names_arr", "__product_states_arr", "__product_short_arr", "__product_category_arr", "__product_greenhouse_arr", "__product_acididty_arr"]
    case_groups = ["", "", "", "", "", ""]
    arr_groups = ["", "", "", "", "", ""]
    def_vals = ["NULL", "NULL", "NULL", "NULL", "+0", "0.0f"]

    with open(os.path.join(os.path.dirname(__file__), "Products.in"), "r") as f:
        line = f.readline()

        while line:
            if line == "\n":
                arr_groups[0] += '\n\t"' + products[-1].name.replace("_", " ") + '", '
                arr_groups[1] += '\n\t"' + products[-1].state + '", '
                arr_groups[2] += '\n\t"' + products[-1].short + '", '
                arr_groups[3] += '\n\t"' + products[-1].category + '", '

                if products[-1].greenhouse is None:
                    arr_groups[4] += '\n\t' + def_vals[4] + ', '
                else:
                    arr_groups[4] += '\n\t' + products[-1].greenhouse + ', '


                if products[-1].acidity is None:
                    arr_groups[5] += '\n\t' + def_vals[5] + ', '
                elif products[-1].acidity.count("."):
                    arr_groups[5] += '\n\t' + products[-1].acidity + 'f, '
                else:
                    arr_groups[5] += '\n\t' + products[-1].acidity + '.0f, '

            elif line[0] == "\t" or line[0] == " ":
                key = line[:line.index(":")].strip()
                value = line[line.index(":")+2:].strip()

                if key == "Short":
                    products[-1].addShort(value)
                elif key == "State":
                    products[-1].addState(value)
                elif key == "Category":
                    products[-1].addCategory(value)
                elif key == "Greenhouse":
                    products[-1].addGreenhouseEffect(value)
                elif key == "Acidity":
                    products[-1].addAcidity(value)
                else:
                    pass
                
            else:
                products.append(Product(line.strip().replace(" ", "_")))
            
            line = f.readline()

    arr_groups[0] = arr_groups[0][1:-2]
    arr_groups[1] = arr_groups[1][1:-2]
    arr_groups[2] = arr_groups[2][1:-2]
    arr_groups[3] = arr_groups[3][1:-2]
    arr_groups[4] = arr_groups[4][1:-2]
    arr_groups[5] = arr_groups[5][1:-2]

    with open(os.path.join(os.path.dirname(__file__), "..\..\source\Production\Enums\Product.h"), "w") as f:
        products_names = [p.name for p in products]
        f.write(product_h_format.format(
            ",\n\t".join(products_names),
            ";\n".join(product_funcs) + ";\n"
        ))

    with open(os.path.join(os.path.dirname(__file__), "..\..\source\Production\Enums\Product.c"), "w") as f:
        f.write(product_c_start)

        for i in range(len(product_funcs)):
            f.write(function_format_arr.format(product_funcs[i], data_types[i], arr_names[i], arr_groups[i]))



if __name__ == "__main__":
    main()
