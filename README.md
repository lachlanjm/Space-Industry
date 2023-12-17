# Space Industry

## World Settings
### ./tools/Production/ProductionChains.in
Defines all of the production recipes.

### ./tools/Production/Products.in
Defines all possible products and their properties.

### ./tools/Transport/Map.in
Defines the outlay of the map. Its nodes and connections between each node.

## Build process

### Pre-build Scripts
These scripts define the environment and whenever the world settings are modified, need to be run before compiling in order for the changes to make effect:
* ./tools/Production/productCreationScript.py
* ./tools/Production/productionChainCreationScript.py
* ./tools/Transport/mapCreationScript.py

Either manually complete this task or execute this command from the main directory:
```bash
python3 ./tools/preBuildScript.py
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
