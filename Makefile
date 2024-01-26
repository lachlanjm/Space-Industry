.DEFAULT_GOAL = build

CC := gcc
BUILD_DIR := build
SRC_DIR := source

BUILD_OBJ_DIR := Objects
CORE_DIR := Core
SIM_DIR := Simulation
_ENV_DIR := Environment
GUI_DIR := GUI
MAIN_DIR := Main
MAN_DIR := Management
MAR_DIR := Markets
PRO_DIR := Production
TRA_DIR := Transport

BUILD_PATH := .\$(BUILD_DIR)
BUILD_OBJ_PATH := $(BUILD_PATH)\$(BUILD_OBJ_DIR)

SRC_PATH := .\$(SRC_DIR)
CORE_PATH := $(SRC_PATH)\$(CORE_DIR)
GUI_PATH := $(SRC_PATH)\$(GUI_DIR)
SIM_PATH := $(SRC_PATH)\$(SIM_DIR)

_ENV_PATH := $(SIM_PATH)\$(_ENV_DIR)
MAIN_PATH := $(SIM_PATH)\$(MAIN_DIR)
MAN_PATH := $(SIM_PATH)\$(MAN_DIR)
MAR_PATH := $(SIM_PATH)\$(MAR_DIR)
PRO_PATH := $(SIM_PATH)\$(PRO_DIR)
TRA_PATH := $(SIM_PATH)\$(TRA_DIR)

OBJ_FILES := $(BUILD_OBJ_PATH)\TransportConnectionType.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\TransportNode.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Map.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\MarketMap.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\AppState.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\SaveAppState.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LoadAppState.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Core.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsContract.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsManager.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\FactoryManager.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Order.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductMarket.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Product.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductionRecipe.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Factory.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Stockpile.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Vehicle.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\MainMenu.c.o

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
	make prebuild
	make build
	make run

.PHONY: prebuild
prebuild:
	python3 ./tools/preBuildScript.py

.PHONY: run
run:
	.\IndustryApp.exe > $(BUILD_PATH)\run_time.log

.PHONY: build
build:
	make build_no_log 2> $(BUILD_PATH)\make_build.log

.PHONY: build_no_log
build_no_log:
#	mkdir $(BUILD_OBJ_PATH)

	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Enums\TransportConnectionType.h -o $(BUILD_OBJ_PATH)\TransportConnectionType.h.gch 
	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Enums\TransportNode.h -o $(BUILD_OBJ_PATH)\TransportNode.h.gch 
	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Structures\Map.h -o $(BUILD_OBJ_PATH)\Map.h.gch 
	$(CC) $(CFLAGS) -c $(_ENV_PATH)\Structures\MarketMap.h -o $(BUILD_OBJ_PATH)\MarketMap.h.gch 

	$(CC) $(CFLAGS) -c $(MAIN_PATH)\AppState\AppState.h -o $(BUILD_OBJ_PATH)\AppState.h.gch 
	$(CC) $(CFLAGS) -c $(MAIN_PATH)\AppState\SaveAppState.h -o $(BUILD_OBJ_PATH)\SaveAppState.h.gch 
	$(CC) $(CFLAGS) -c $(MAIN_PATH)\AppState\LoadAppState.h -o $(BUILD_OBJ_PATH)\LoadAppState.h.gch 

	$(CC) $(CFLAGS) -c $(CORE_PATH)\Core.h -o $(BUILD_OBJ_PATH)\Core.h.gch 

	$(CC) $(CFLAGS) -c $(MAN_PATH)\Logistics\LogisticsContract.h -o $(BUILD_OBJ_PATH)\LogisticsContract.h.gch 
	$(CC) $(CFLAGS) -c $(MAN_PATH)\Logistics\LogisticsManager.h -o $(BUILD_OBJ_PATH)\LogisticsManager.h.gch 
	$(CC) $(CFLAGS) -c $(MAN_PATH)\Production\FactoryManager.h -o $(BUILD_OBJ_PATH)\FactoryManager.h.gch 
	
	$(CC) $(CFLAGS) -c $(MAR_PATH)\Structures\Order.h -o $(BUILD_OBJ_PATH)\Order.h.gch 
	$(CC) $(CFLAGS) -c $(MAR_PATH)\Structures\ProductMarket.h -o $(BUILD_OBJ_PATH)\ProductMarket.h.gch 

	$(CC) $(CFLAGS) -c $(PRO_PATH)\Enums\Product.h -o $(BUILD_OBJ_PATH)\Product.h.gch 
	$(CC) $(CFLAGS) -c $(PRO_PATH)\Enums\ProductionRecipe.h -o $(BUILD_OBJ_PATH)\ProductionRecipe.h.gch 
	$(CC) $(CFLAGS) -c $(PRO_PATH)\Structures\Factory.h -o $(BUILD_OBJ_PATH)\Factory.h.gch 
	$(CC) $(CFLAGS) -c $(PRO_PATH)\Structures\Stockpile.h -o $(BUILD_OBJ_PATH)\Stockpile.h.gch 

	$(CC) $(CFLAGS) -c $(TRA_PATH)\Structures\Vehicle.h -o $(BUILD_OBJ_PATH)\Vehicle.h.gch 

	$(CC) $(CFLAGS) -c $(GUI_PATH)\MainMenu.h -o $(BUILD_OBJ_PATH)\MainMenu.h.gch 

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(_ENV_PATH)\Enums\TransportConnectionType.c -o $(BUILD_OBJ_PATH)\TransportConnectionType.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(_ENV_PATH)\Enums\TransportNode.c -o $(BUILD_OBJ_PATH)\TransportNode.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(_ENV_PATH)\Structures\Map.c -o $(BUILD_OBJ_PATH)\Map.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(_ENV_PATH)\Structures\MarketMap.c -o $(BUILD_OBJ_PATH)\MarketMap.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAIN_PATH)\AppState\AppState.c -o $(BUILD_OBJ_PATH)\AppState.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAIN_PATH)\AppState\SaveAppState.c -o $(BUILD_OBJ_PATH)\SaveAppState.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAIN_PATH)\AppState\LoadAppState.c -o $(BUILD_OBJ_PATH)\LoadAppState.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(CORE_PATH)\Core.c -o $(BUILD_OBJ_PATH)\Core.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAN_PATH)\Logistics\LogisticsContract.c -o $(BUILD_OBJ_PATH)\LogisticsContract.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAN_PATH)\Logistics\LogisticsManager.c -o $(BUILD_OBJ_PATH)\LogisticsManager.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAN_PATH)\Production\FactoryManager.c -o $(BUILD_OBJ_PATH)\FactoryManager.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAR_PATH)\Structures\Order.c -o $(BUILD_OBJ_PATH)\Order.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(MAR_PATH)\Structures\ProductMarket.c -o $(BUILD_OBJ_PATH)\ProductMarket.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(PRO_PATH)\Enums\Product.c -o $(BUILD_OBJ_PATH)\Product.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(PRO_PATH)\Enums\ProductionRecipe.c -o $(BUILD_OBJ_PATH)\ProductionRecipe.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(PRO_PATH)\Structures\Factory.c -o $(BUILD_OBJ_PATH)\Factory.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(PRO_PATH)\Structures\Stockpile.c -o $(BUILD_OBJ_PATH)\Stockpile.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(TRA_PATH)\Structures\Vehicle.c -o $(BUILD_OBJ_PATH)\Vehicle.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(GUI_PATH)\MainMenu.c -o $(BUILD_OBJ_PATH)\MainMenu.c.o

	$(CC) $(CFLAGS) $(LIBS) -I $(BUILD_OBJ_PATH) $(OBJ_FILES) $(LOCAL_LIBS) -o .\IndustryApp.exe

.PHONY: clean
clean:
#	NEED TO UPDATE
	rm -r $(BUILD_DIR)
