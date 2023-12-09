import os

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
case_groups = ["", "", "", "", "", ""]
def_vals = ["NULL", "NULL", "NULL", "NULL", "+0", "0.0f"]

with open(os.path.join(os.path.dirname(__file__), "Products.in"), "r") as f:
    line = f.readline()

    while line:
        if line == "\n":
            case_groups[0] += case_format.format(products[-1], '"' + products[-1].name.replace("_", " ") + '"')
            case_groups[1] += case_format.format(products[-1], '"' + products[-1].state + '"')
            case_groups[2] += case_format.format(products[-1], '"' + products[-1].short + '"')
            case_groups[3] += case_format.format(products[-1], '"' + products[-1].category + '"')

            if products[-1].greenhouse is not None:
                case_groups[4] += case_format.format(products[-1], products[-1].greenhouse)

            if products[-1].acidity is not None:
                if products[-1].acidity.count("."):
                    case_groups[5] += case_format.format(products[-1], products[-1].acidity + 'f')
                else:
                    case_groups[5] += case_format.format(products[-1], products[-1].acidity + '.0f')

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

with open(os.path.join(os.path.dirname(__file__), "..\Enums\Product.h"), "w") as f:
    products_names = [p.name for p in products]
    f.write(product_h_format.format(
        ",\n\t".join(products_names),
        ";\n".join(product_funcs) + ";\n"
    ))

with open(os.path.join(os.path.dirname(__file__), "..\Enums\Product.c"), "w") as f:
    f.write(product_c_start)

    for i in range(len(product_funcs)):
        f.write(function_format.format(product_funcs[i], case_groups[i], def_vals[i]))