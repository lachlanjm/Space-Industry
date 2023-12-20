# Conventions

## General

### Core Principles
* Be simple
* Be concise
* Be descriptive
* Maintain modulairty and scope as best as possible
* Reuse don't redefine, i.e. add functions not definitions
* Adhere to a common standard, unless the above principes are compromised.

### File structure
For each file, they are sorted by what they each represent.
Each group of files is sorted into differents categories; i.e. "Markets", "Production", "Transport", etc.
From there, each category is split into "Enums" and "Structures" and the source code files are split accordingly.
Some examples of filepaths from the project's root directory include:
```
.\source\Production\Enums\Product.h
.\source\Environment\Enums\TransportNode.h
.\source\Transport\Structures\Vehicle.h
.\source\Markets\Structures\Order.h
```
The only exception is the "Management" directory where the second directory is simply a subcategory with no added "Enums" or "Structures".

### Variables
Be short, concise and descriptive. When selecting types of variables, try to be as explicit as possible. I.e. use `int8_t`, instead of `short int`. When naming variables, use camelCase for variables of same name as type:
```c
ProductionRecipe productionRecipe;
```
Avoid that if possible, try to use different more descriptive names where you otherwise use snake_case:
```c
Stockpile* stockpiles_in;
```

### Functions
Use the following format for function definitions:
```c
void function_name(...)
{
    ...
}
```
For naming conventions, use the Structures naming conventions.

### If Else statements
Follow this convention:
```c
if (<conditions>)
{
    ...
}
else if (<conditions>)
{
    ...
}
else 
{
    ...
}
```

### For loops
Follow this convention:
```c
for (<initialisation>; <declaration>; <increment>)
{
    ...
}
```

## Structures

### Name
Use PascalCase for structures names.
```c 
ProductMarket
```

### Source files
For each struct that is meant to be avaliable externally, make one header file (`.h`) and one source code file (`.c`) with the same name as the struct. If it is not meant to be avaliable externally, include it in the singular file that requires it.

### Definition
Always use `typedef` to define the structs meant for external use. If meant for a singular file, do not use `typedef`.
```c
[typedef] struct <struct_name> {
    ...
} [<struct_name>];
```

### Member variables naming
If the variable is the same name as the variable type, use camelCase. E.g:
```c
ProductionRecipe productionRecipe;
```
Otherwise, use snake_case. E.g:
```c
Stockpile* stockpiles_in;
```

### Related enum functions
I.e. instance methods. Functions that take a singular ptr to an instance of the struct as the first parameter (similar to Python's self parameter) use camelCase. E.g:
```c
void assignNewFactoryValues(Factory* factory, [...]);
```
For parameters in these functions, use the same naming convention as for member variables, however, try to avoid naming parameters the same as their type unless it is the first parameter.
<br><br>
For other functions, use snake_case. E.g:
```c
int multiply_integers(int num_1, int num_2, [...]);
```

## Enums

### Name
Use the same conventions as Structures.

### Source files
Use the same conventions as Structures.

### Definition
Use the same conventions as Structures.

### Member variables naming
Use the same conventions as Structures.

### Related struct functions
Use the same conventions as Structures.
