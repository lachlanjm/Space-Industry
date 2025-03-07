.DEFAULT_GOAL = build

CC := gcc
APP_DIR := app
BUILD_DIR := build
SRC_DIR := source

# SAVE_DIR := saves
# START_DIR := starts
BUILD_OBJ_DIR := Objects
# CORE_DIR := Core
# SIM_DIR := Simulation
# _ENV_DIR := Environment
GUI_DIR := GUI
# HELP_DIR := Helpers
# MAIN_DIR := Main
# MAN_DIR := Management
# MAR_DIR := Markets
# PRO_DIR := Production
# TRA_DIR := Transport
# WIN_DIR := Windows

APP_PATH := .\$(APP_DIR)
# SAVE_PATH := $(APP_PATH)\$(SAVE_DIR)
# START_PATH := $(APP_PATH)\$(START_DIR)

BUILD_PATH := .\$(BUILD_DIR)
BUILD_OBJ_PATH := $(BUILD_PATH)\$(BUILD_OBJ_DIR)

SRC_PATH := .\$(SRC_DIR)
# CORE_PATH := $(SRC_PATH)\$(CORE_DIR)
GUI_PATH := $(SRC_PATH)\$(GUI_DIR)
# HELP_PATH := $(SRC_PATH)\$(HELP_DIR)
# SIM_PATH := $(SRC_PATH)\$(SIM_DIR)
# 
# _ENV_PATH := $(SIM_PATH)\$(_ENV_DIR)
# MAIN_PATH := $(SIM_PATH)\$(MAIN_DIR)
# MAN_PATH := $(SIM_PATH)\$(MAN_DIR)
# MAR_PATH := $(SIM_PATH)\$(MAR_DIR)
# PRO_PATH := $(SIM_PATH)\$(PRO_DIR)
# TRA_PATH := $(SIM_PATH)\$(TRA_DIR)
# WIN_PATH := $(GUI_PATH)\$(WIN_DIR)

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
OBJ_FILES += $(BUILD_OBJ_PATH)\Company.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Order.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductMarket.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Government.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocalPopulation.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Product.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductionRecipe.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Factory.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Stockpile.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\Vehicle.c.o

OBJ_FILES += $(BUILD_OBJ_PATH)\PopupWindow.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\CompanyList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\CompanyMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\FactoryMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\GovernmentList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\GovernmentMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LoadFileMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocalPopulationList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocalPopulationMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocationGroup.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LocationMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsContractMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsManagerList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\LogisticsManagerMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\MainMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\OrderMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductMarketList.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\ProductMarketMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\SaveFileMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\SimulationControlMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\StockpileMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\VehicleMenu.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\DirectoryReading.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\HistoryArray.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\HistoryArrayAvg.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\HistoryWtdAvgArray.c.o
OBJ_FILES += $(BUILD_OBJ_PATH)\HistoryIterator.c.o

GUI_LIBS_PATH := $(GUI_PATH)\libs

CFLAGS := -std=c23 -Wall -g -DGLEW_STATIC

ifeq ($(OS),Windows_NT)
	CFLAGS += -D_WIN64
	LIBS = -lglfw3 -lopengl32 -lm -lGLU32 -lGLEW32
	WINDOWS_GUI_LIBS := $(GUI_LIBS_PATH)\Windows
	LOCAL_LIBS = $(WINDOWS_GUI_LIBS)\glfw3dll.lib $(WINDOWS_GUI_LIBS)\OpenGL32.lib $(WINDOWS_GUI_LIBS)\glew32.lib
else
	UNAME_S := $(shell uname -s)
	GLFW3 := $(shell pkg-config --libs glfw3)
	ifeq ($(UNAME_S),Darwin)
		CFLAGS += -D__APPLE__
		LIBS := $(GLFW3) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm -lGLEW -L/usr/local/lib
	else
		CFLAGS += -DLINUX
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

.PHONY: auto_info
auto_info:
	@echo $(CC) $(CFLAGS)
	@echo $(BUILD_OBJ_PATH)
	@echo $(BUILD_PATH)\make_build.log

.PHONY: build
build:
	python .\tools\Auto-compiler\auto-compiler.py update

.PHONY: full_build
full_build:
	python .\tools\Auto-compiler\auto-compiler.py full

.PHONY: run
run:
	$(APP_PATH)\IndustryApp.exe $(APP_PATH) > $(APP_PATH)\run_time.log

.PHONY: run_debug
run_debug:
	gdb --args $(APP_PATH)\IndustryApp.exe $(APP_PATH)

.PHONY: final_compile
final_compile:
	$(CC) $(CFLAGS) $(LIBS) -I $(BUILD_OBJ_PATH) $(OBJ_FILES) $(LOCAL_LIBS) -o $(APP_PATH)\IndustryApp.exe

.PHONY: clean
clean:
#	NEED TO UPDATE
	rm -r $(BUILD_DIR)
