CC := gcc
BUILD_DIR := build
SRC_DIR := source

ENV_CLASS := $(_ENV_DIR)\Enums\TransportConnectionType $(_ENV_DIR)\Enums\TransportNode $(_ENV_DIR)\Structures\Map $(_ENV_DIR)\Structures\MarketMap
ENV_FILES := $(ENV_CLASS:%=%.h) $(ENV_CLASS:%=%.c)

_ENV_DIRS := $(SRC_DIR)\Environment\Enums\ $(SRC_DIR)\Environment\Structures\
MAN_DIRS := $(SRC_DIR)\Management\Logistics\ $(SRC_DIR)\Management\Production\
MAR_DIRS := $(SRC_DIR)\Markets\Structures\
PRO_DIRS := $(SRC_DIR)\Production\Enums\ $(SRC_DIR)\Production\Structures\
TRA_DIRS := $(SRC_DIR)\Transport\Enums\ $(SRC_DIR)\Transport\Structures\
SRC_DIRS := $(_ENV_DIRS) $(MAIN_DIR) $(MAN_DIRS) $(MAR_DIRS) $(PRO_DIRS) $(TRA_DIRS)

ALL_CLASS := $(ENV_CLASS)
ALL_FILES := $(ENV_FILES)

OBJ_FILES := .\$(BUILD_DIR)\TransportConnectionType.c.o
OBJ_FILES += .\$(BUILD_DIR)\TransportNode.c.o
OBJ_FILES += .\$(BUILD_DIR)\Map.c.o
OBJ_FILES += .\$(BUILD_DIR)\MarketMap.c.o
OBJ_FILES += .\$(BUILD_DIR)\AppState.c.o
OBJ_FILES += .\$(BUILD_DIR)\SaveAppState.c.o
OBJ_FILES += .\$(BUILD_DIR)\LoadAppState.c.o
OBJ_FILES += .\$(BUILD_DIR)\Core.c.o
OBJ_FILES += .\$(BUILD_DIR)\LogisticsContract.c.o
OBJ_FILES += .\$(BUILD_DIR)\LogisticsManager.c.o
OBJ_FILES += .\$(BUILD_DIR)\FactoryManager.c.o
OBJ_FILES += .\$(BUILD_DIR)\Order.c.o
OBJ_FILES += .\$(BUILD_DIR)\ProductMarket.c.o
OBJ_FILES += .\$(BUILD_DIR)\Product.c.o
OBJ_FILES += .\$(BUILD_DIR)\ProductionRecipe.c.o
OBJ_FILES += .\$(BUILD_DIR)\Factory.c.o
OBJ_FILES += .\$(BUILD_DIR)\Stockpile.c.o
OBJ_FILES += .\$(BUILD_DIR)\Vehicle.c.o

CORE_DIR := Core
SIM_DIR := Simulation
_ENV_DIR := Environment
GUI_DIR := GUI
MAIN_DIR := Main
MAN_DIR := Management
MAR_DIR := Markets
PRO_DIR := Production
TRA_DIR := Transport

CORE_PATH := .\$(SRC_DIR)\$(CORE_DIR)
GUI_PATH := .\$(SRC_DIR)\$(GUI_DIR)
SIM_PATH := .\$(SRC_DIR)\$(SIM_DIR)
_ENV_PATH := $(SIM_PATH)\$(_ENV_DIR)
MAIN_PATH := $(SIM_PATH)\$(MAIN_DIR)
MAN_PATH := $(SIM_PATH)\$(MAN_DIR)
MAR_PATH := $(SIM_PATH)\$(MAR_DIR)
PRO_PATH := $(SIM_PATH)\$(PRO_DIR)
TRA_PATH := $(SIM_PATH)\$(TRA_DIR)

GUI_LIBS_PATH := $(GUI_PATH)\libs

CFLAGS := -Wall -g -DGLEW_STATIC -D_WIN64

ifeq ($(OS),Windows_NT)
	LIBS = -lglfw3 -lopengl32 -lm -lGLU32 -lGLEW32
	WINDOWS_GUI_LIBS := $(GUI_LIBS_PATH)\Windows
	LOCAL_LIBS = $(WINDOWS_GUI_LIBS)\glfw3dll.lib $(WINDOWS_GUI_LIBS)\OpenGL32.lib $(WINDOWS_GUI_LIBS)\glew32.lib
else
	UNAME_S := $(shell uname -s)
	GLFW3 := $(shell pkg-config --libs glfw3)
	ifeq ($(UNAME_S),Darwin)
		LIBS := $(GLFW3) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm -lGLEW -L/usr/local/lib
	else
		LIBS = $(GLFW3) -lGL -lm -lGLU -lGLEW
	endif
endif

.PHONY: all
all:
	make build 2>make_log.out

.PHONY: build
build:
#	mkdir .\$(BUILD_DIR)

	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Enums\TransportConnectionType.h -o .\$(BUILD_DIR)\TransportConnectionType.h.gch 
	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Enums\TransportNode.h -o .\$(BUILD_DIR)\TransportNode.h.gch 
	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Structures\Map.h -o .\$(BUILD_DIR)\Map.h.gch 
	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Structures\MarketMap.h -o .\$(BUILD_DIR)\MarketMap.h.gch 

	$(CC) $(CFLAGS) -c $(MAIN_PATH)\AppState\AppState.h -o .\$(BUILD_DIR)\AppState.h.gch 
	$(CC) $(CFLAGS) -c $(MAIN_PATH)\AppState\SaveAppState.h -o .\$(BUILD_DIR)\SaveAppState.h.gch 
	$(CC) $(CFLAGS) -c $(MAIN_PATH)\AppState\LoadAppState.h -o .\$(BUILD_DIR)\LoadAppState.h.gch 

	$(CC) $(CFLAGS) -c $(CORE_PATH)\Core.h -o .\$(BUILD_DIR)\Core.h.gch 

	$(CC) $(CFLAGS) -c $(MAN_PATH)\Logistics\LogisticsContract.h -o .\$(BUILD_DIR)\LogisticsContract.h.gch 
	$(CC) $(CFLAGS) -c $(MAN_PATH)\Logistics\LogisticsManager.h -o .\$(BUILD_DIR)\LogisticsManager.h.gch 
	$(CC) $(CFLAGS) -c $(MAN_PATH)\Production\FactoryManager.h -o .\$(BUILD_DIR)\FactoryManager.h.gch 
	
	$(CC) $(CFLAGS) -c $(MAR_PATH)\Structures\Order.h -o .\$(BUILD_DIR)\Order.h.gch 
	$(CC) $(CFLAGS) -c $(MAR_PATH)\Structures\ProductMarket.h -o .\$(BUILD_DIR)\ProductMarket.h.gch 

	$(CC) $(CFLAGS) -c $(PRO_PATH)\Enums\Product.h -o .\$(BUILD_DIR)\Product.h.gch 
	$(CC) $(CFLAGS) -c $(PRO_PATH)\Enums\ProductionRecipe.h -o .\$(BUILD_DIR)\ProductionRecipe.h.gch 
	$(CC) $(CFLAGS) -c $(PRO_PATH)\Structures\Factory.h -o .\$(BUILD_DIR)\Factory.h.gch 
	$(CC) $(CFLAGS) -c $(PRO_PATH)\Structures\Stockpile.h -o .\$(BUILD_DIR)\Stockpile.h.gch 

	$(CC) $(CFLAGS) -c $(TRA_PATH)\Structures\Vehicle.h -o .\$(BUILD_DIR)\Vehicle.h.gch 

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(_ENV_PATH)\Enums\TransportConnectionType.c -o .\$(BUILD_DIR)\TransportConnectionType.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(_ENV_PATH)\Enums\TransportNode.c -o .\$(BUILD_DIR)\TransportNode.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(_ENV_PATH)\Structures\Map.c -o .\$(BUILD_DIR)\Map.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(_ENV_PATH)\Structures\MarketMap.c -o .\$(BUILD_DIR)\MarketMap.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAIN_PATH)\AppState\AppState.c -o .\$(BUILD_DIR)\AppState.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAIN_PATH)\AppState\SaveAppState.c -o .\$(BUILD_DIR)\SaveAppState.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAIN_PATH)\AppState\LoadAppState.c -o .\$(BUILD_DIR)\LoadAppState.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(CORE_PATH)\Core.c -o .\$(BUILD_DIR)\Core.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAN_PATH)\Logistics\LogisticsContract.c -o .\$(BUILD_DIR)\LogisticsContract.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAN_PATH)\Logistics\LogisticsManager.c -o .\$(BUILD_DIR)\LogisticsManager.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAN_PATH)\Production\FactoryManager.c -o .\$(BUILD_DIR)\FactoryManager.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAR_PATH)\Structures\Order.c -o .\$(BUILD_DIR)\Order.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(MAR_PATH)\Structures\ProductMarket.c -o .\$(BUILD_DIR)\ProductMarket.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(PRO_PATH)\Enums\Product.c -o .\$(BUILD_DIR)\Product.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(PRO_PATH)\Enums\ProductionRecipe.c -o .\$(BUILD_DIR)\ProductionRecipe.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(PRO_PATH)\Structures\Factory.c -o .\$(BUILD_DIR)\Factory.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(PRO_PATH)\Structures\Stockpile.c -o .\$(BUILD_DIR)\Stockpile.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c $(TRA_PATH)\Structures\Vehicle.c -o .\$(BUILD_DIR)\Vehicle.c.o

	$(CC) $(CFLAGS) $(LIBS) -I .\$(BUILD_DIR) $(OBJ_FILES) $(LOCAL_LIBS) -o .\IndustryApp.exe

.PHONY: clean
clean:
#	NEED TO UPDATE
	rm -r .\$(BUILD_DIR)
