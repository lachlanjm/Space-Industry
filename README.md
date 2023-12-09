# Space Industry

## World Settings
### ./Production/Build_Agents/ProductionChains.in
Defines all of the production recipes.

### ./Production/Build_Agents/Products.in
Defines all possible products and their properties.

### ./Transport/Build_Agents/Map.in
Defines the outlay of the map. Its nodes and connections between each node.

## Build process

### Pre-build Scripts
Run these scripts before the compiler:
* ./Production/Build_Agents/productCreationScript.py
* ./Production/Build_Agents/productionChainCreationScript.py
* ./Transport/Build_Agents/mapCreationScript.py

Either manually complete this task or execute this command from the main directory:
```bash
python3 ./Production/Build_Agents/productCreationScript.py && python3 ./Production/Build_Agents/productCreationScript.py && python3 ./Production/Build_Agents/productCreationScript.py
```

### Build command
Execute this build command:
```bash
gcc -O3 some_script.c
```

## Execute the application
Run this command:
```bash
a.exe
```
