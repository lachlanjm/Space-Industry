# Space Industry

## Dependencies

### Compiling Builds
The tools needed for compilation, including modifying world settings:
* Python 3.x
* C compiler, C99 compatible (only GCC is officially supported)

### Running Builds
Nothing.

## World Settings
### Production Recipes settings
Location: [./tools/Production/ProductionChains.in](./tools/Production/ProductionChains.in) <br>
Defines all of the production recipes.

### Product settings
Location: [./tools/Production/Products.in](./tools/Production/Products.in) <br>
Defines all possible products and their properties.

### Map settings
Location: [./tools/Environment/Map.in](./tools/Environment/Map.in) <br>
Defines the outlay of the map. Its nodes and connections between each node.

## Build process

### Pre-build Scripts
These scripts define the environment and whenever the world settings are modified, need to be run before compiling in order for the changes to make effect:
* [./tools/Production/productCreationScript.py](./tools/Production/productCreationScript.py)
* [./tools/Production/productionChainCreationScript.py](./tools/Production/productionChainCreationScript.py)
* [./tools/Environment/mapCreationScript.py](./tools/Environment/mapCreationScript.py)
* [./tools/Environment/marketMapCreationScript.py](./tools/Environment/marketMapCreationScript.py)

Either manually complete this task or execute this [script](./tools/preBuildScript.py). Example of how to run it from the main directory:
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
