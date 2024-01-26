import os

def main():
    market_map_h = """#ifndef MARKET_MAP_H
#define MARKET_MAP_H

#include "..\..\Markets\Structures\ProductMarket.h"
#include "..\..\Production\Enums\Product.h"
#include "..\Enums\TransportNode.h"

{0}
#endif
"""

    market_map_c_start = """#include "MarketMap.h"

"""

    function_format = """static {1} {2}[] =
{{
{3}
}};
{0} {{
    return &{2}[location][product];
}}

"""

    # Program starts

    products = []
    locations = []

    with open(os.path.join(os.path.dirname(__file__), "..\Production\Products.in"), "r") as f:
        line = f.readline()

        while line:
            if line[0] not in ["\n", "\t", " "]:
                products.append(line.strip().replace(" ", "_"))
            
            line = f.readline()

    with open(os.path.join(os.path.dirname(__file__), "Map.in"), "r") as f:
        line = f.readline()

        while line:
            if line[0] not in ["\n", "\t", " "]:
                locations.append(line.strip().replace(" ", "_"))
            
            line = f.readline()
    
    # GOT PRODUCTS AND LOCATIONS

    functions = ["ProductMarket* getProductMarketAtLocation(const TransportNode location, const Product product)"]

    with open(os.path.join(os.path.dirname(__file__), "..\..\source\Simulation\Environment\Structures\MarketMap.h"), "w") as f:
        f.write(market_map_h.format(
            ";\n".join(functions) + ";\n"
        ))

    with open(os.path.join(os.path.dirname(__file__), "..\..\source\Simulation\Environment\Structures\MarketMap.c"), "w") as f:
        f.write(market_map_c_start)

        type_ = "ProductMarket"
        f.write(function_format.format(functions[0], f"{type_}*", "__product_market_at_location_arr__", 
            str(
                [f"\n\t({type_}<|>) {[f'{{{product}, NULL, NULL}}' for product in products]}" for location in locations]
            ).replace("[", "{").replace("]", "}").replace("\\t", "\t").replace("\\n", "\n").replace("'", "").replace('"', "").replace("<|>", "[]")[2:-1]
        ))

if __name__ == "__main__":
    main()