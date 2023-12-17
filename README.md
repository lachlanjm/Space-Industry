# Space Industry

## World Settings
### ./tools/Production/Build_Agents/ProductionChains.in
Defines all of the production recipes.

### ./tools/Production/Build_Agents/Products.in
Defines all possible products and their properties.

### ./tools/Transport/Build_Agents/Map.in
Defines the outlay of the map. Its nodes and connections between each node.

## Build process

### Pre-build Scripts
These scripts define the environment and whenever the world settings are modified, need to be run before compiling in order for the changes to make effect:
* ./tools/Production/Build_Agents/productCreationScript.py
* ./tools/Production/Build_Agents/productionChainCreationScript.py
* ./tools/Transport/Build_Agents/mapCreationScript.py

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
