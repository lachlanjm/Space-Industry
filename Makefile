.DEFAULT_GOAL = build

CC := gcc
APP_DIR := app
BUILD_DIR := build
SRC_DIR := source

SAVE_DIR := saves
START_DIR := starts
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
WIN_DIR := Windows

APP_PATH := .\$(APP_DIR)
SAVE_PATH := $(APP_PATH)\$(SAVE_DIR)
START_PATH := $(APP_PATH)\$(START_DIR)

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
WIN_PATH := $(GUI_PATH)\$(WIN_DIR)

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
OBJ_FILES += $(BUILD_OBJ_PATH)\PopupWindow.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\FactoryMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\FactoryList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocationGroup.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocationMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsContractMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsManagerList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsManagerMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\MainMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\OrderMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductMarketList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductMarketMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\StockpileMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\VehicleMenu.c.o

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
	python ./tools/preBuildScript.py

.PHONY: run
run:
	$(APP_PATH)\IndustryApp.exe $(APP_PATH) > $(APP_PATH)\run_time.log

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

	$(CC) $(CFLAGS) -c $(GUI_PATH)\Enums\WindowTypes.h -o $(BUILD_OBJ_PATH)\WindowTypes.h.gch 
	$(CC) $(CFLAGS) -c $(GUI_PATH)\Structures\PopupWindow.h -o $(BUILD_OBJ_PATH)\PopupWindow.h.gch 

	$(CC) $(CFLAGS) -c $(WIN_PATH)\FactoryMenu.h -o $(BUILD_OBJ_PATH)\FactoryMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\FactoryList.h -o $(BUILD_OBJ_PATH)\FactoryList.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\LocationGroup.h -o $(BUILD_OBJ_PATH)\LocationGroup.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\LocationMenu.h -o $(BUILD_OBJ_PATH)\LocationMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\LogisticsContractMenu.h -o $(BUILD_OBJ_PATH)\LogisticsContractMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\LogisticsManagerList.h -o $(BUILD_OBJ_PATH)\LogisticsManagerList.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\LogisticsManagerMenu.h -o $(BUILD_OBJ_PATH)\LogisticsManagerMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\MainMenu.h -o $(BUILD_OBJ_PATH)\MainMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\OrderMenu.h -o $(BUILD_OBJ_PATH)\OrderMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\ProductMarketList.h -o $(BUILD_OBJ_PATH)\ProductMarketList.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\ProductMarketMenu.h -o $(BUILD_OBJ_PATH)\ProductMarketMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\StockpileMenu.h -o $(BUILD_OBJ_PATH)\StockpileMenu.h.gch 
	$(CC) $(CFLAGS) -c $(WIN_PATH)\VehicleMenu.h -o $(BUILD_OBJ_PATH)\VehicleMenu.h.gch 



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

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(GUI_PATH)\Structures\PopupWindow.c -o $(BUILD_OBJ_PATH)\PopupWindow.c.o

	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\FactoryMenu.c -o $(BUILD_OBJ_PATH)\FactoryMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\FactoryList.c -o $(BUILD_OBJ_PATH)\FactoryList.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\LocationGroup.c -o $(BUILD_OBJ_PATH)\LocationGroup.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\LocationMenu.c -o $(BUILD_OBJ_PATH)\LocationMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\LogisticsContractMenu.c -o $(BUILD_OBJ_PATH)\LogisticsContractMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\LogisticsManagerList.c -o $(BUILD_OBJ_PATH)\LogisticsManagerList.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\LogisticsManagerMenu.c -o $(BUILD_OBJ_PATH)\LogisticsManagerMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\MainMenu.c -o $(BUILD_OBJ_PATH)\MainMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\OrderMenu.c -o $(BUILD_OBJ_PATH)\OrderMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\ProductMarketList.c -o $(BUILD_OBJ_PATH)\ProductMarketList.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\ProductMarketMenu.c -o $(BUILD_OBJ_PATH)\ProductMarketMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\StockpileMenu.c -o $(BUILD_OBJ_PATH)\StockpileMenu.c.o
	$(CC) $(CFLAGS) -I $(BUILD_OBJ_PATH) -c $(WIN_PATH)\VehicleMenu.c -o $(BUILD_OBJ_PATH)\VehicleMenu.c.o

	$(CC) $(CFLAGS) $(LIBS) -I $(BUILD_OBJ_PATH) $(OBJ_FILES) $(LOCAL_LIBS) -o $(APP_PATH)\IndustryApp.exe

.PHONY: clean
clean:
#	NEED TO UPDATE
	rm -r $(BUILD_DIR)
