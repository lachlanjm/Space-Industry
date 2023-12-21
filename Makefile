CC := gcc
BUILD_DIR := build
SRC_DIR := source

ENV_CLASS := $(ENV_DIR)\Enums\TransportConnectionType $(ENV_DIR)\Enums\TransportNode $(ENV_DIR)\Structures\Map $(ENV_DIR)\Structures\MarketMap
ENV_FILES := $(ENV_CLASS:%=%.h) $(ENV_CLASS:%=%.c)

ENV_DIRS := $(SRC_DIR)\Environment\Enums\ $(SRC_DIR)\Environment\Structures\
MAN_DIRS := $(SRC_DIR)\Management\Logistics\ $(SRC_DIR)\Management\Production\
MAR_DIRS := $(SRC_DIR)\Markets\Structures\
PRO_DIRS := $(SRC_DIR)\Production\Enums\ $(SRC_DIR)\Production\Structures\
TRA_DIRS := $(SRC_DIR)\Transport\Enums\ $(SRC_DIR)\Transport\Structures\
SRC_DIRS := $(ENV_DIRS) $(MAIN_DIR) $(MAN_DIRS) $(MAR_DIRS) $(PRO_DIRS) $(TRA_DIRS)

ALL_CLASS := $(ENV_CLASS)
ALL_FILES := $(ENV_FILES)

OBJ_FILES := .\$(BUILD_DIR)\TransportConnectionType.c.o
OBJ_FILES += .\$(BUILD_DIR)\TransportNode.c.o
OBJ_FILES += .\$(BUILD_DIR)\Map.c.o
OBJ_FILES += .\$(BUILD_DIR)\MarketMap.c.o
OBJ_FILES += .\$(BUILD_DIR)\AppState.c.o
OBJ_FILES += .\$(BUILD_DIR)\SaveAppState.c.o
OBJ_FILES += .\$(BUILD_DIR)\LoadAppState.c.o
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

ENV_DIR := Environment
MAIN_DIR := Main
MAN_DIR := Management
MAR_DIR := Markets
PRO_DIR := Production
TRA_DIR := Transport

CFLAGS := -Wall -O3 


.PHONY: all
all:
#	mkdir .\$(BUILD_DIR)

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Enums\TransportConnectionType.h -o .\$(BUILD_DIR)\TransportConnectionType.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Enums\TransportNode.h -o .\$(BUILD_DIR)\TransportNode.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Structures\Map.h -o .\$(BUILD_DIR)\Map.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Structures\MarketMap.h -o .\$(BUILD_DIR)\MarketMap.h.gch 

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAIN_DIR)\AppState.h -o .\$(BUILD_DIR)\AppState.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAIN_DIR)\SaveAppState.h -o .\$(BUILD_DIR)\SaveAppState.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAIN_DIR)\LoadAppState.h -o .\$(BUILD_DIR)\LoadAppState.h.gch 

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAN_DIR)\Logistics\LogisticsContract.h -o .\$(BUILD_DIR)\LogisticsContract.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAN_DIR)\Logistics\LogisticsManager.h -o .\$(BUILD_DIR)\LogisticsManager.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAN_DIR)\Production\FactoryManager.h -o .\$(BUILD_DIR)\FactoryManager.h.gch 
	
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAR_DIR)\Structures\Order.h -o .\$(BUILD_DIR)\Order.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAR_DIR)\Structures\ProductMarket.h -o .\$(BUILD_DIR)\ProductMarket.h.gch 

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Enums\Product.h -o .\$(BUILD_DIR)\Product.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Enums\ProductionRecipe.h -o .\$(BUILD_DIR)\ProductionRecipe.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Structures\Factory.h -o .\$(BUILD_DIR)\Factory.h.gch 
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Structures\Stockpile.h -o .\$(BUILD_DIR)\Stockpile.h.gch 

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(TRA_DIR)\Structures\Vehicle.h -o .\$(BUILD_DIR)\Vehicle.h.gch 

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(ENV_DIR)\Enums\TransportConnectionType.c -o .\$(BUILD_DIR)\TransportConnectionType.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(ENV_DIR)\Enums\TransportNode.c -o .\$(BUILD_DIR)\TransportNode.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(ENV_DIR)\Structures\Map.c -o .\$(BUILD_DIR)\Map.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(ENV_DIR)\Structures\MarketMap.c -o .\$(BUILD_DIR)\MarketMap.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAIN_DIR)\AppState.c -o .\$(BUILD_DIR)\AppState.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAIN_DIR)\SaveAppState.c -o .\$(BUILD_DIR)\SaveAppState.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAIN_DIR)\LoadAppState.c -o .\$(BUILD_DIR)\LoadAppState.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAN_DIR)\Logistics\LogisticsContract.c -o .\$(BUILD_DIR)\LogisticsContract.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAN_DIR)\Logistics\LogisticsManager.c -o .\$(BUILD_DIR)\LogisticsManager.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAN_DIR)\Production\FactoryManager.c -o .\$(BUILD_DIR)\FactoryManager.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAR_DIR)\Structures\Order.c -o .\$(BUILD_DIR)\Order.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(MAR_DIR)\Structures\ProductMarket.c -o .\$(BUILD_DIR)\ProductMarket.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(PRO_DIR)\Enums\Product.c -o .\$(BUILD_DIR)\Product.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(PRO_DIR)\Enums\ProductionRecipe.c -o .\$(BUILD_DIR)\ProductionRecipe.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(PRO_DIR)\Structures\Factory.c -o .\$(BUILD_DIR)\Factory.c.o
	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(PRO_DIR)\Structures\Stockpile.c -o .\$(BUILD_DIR)\Stockpile.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR)  -c .\$(SRC_DIR)\$(TRA_DIR)\Structures\Vehicle.c -o .\$(BUILD_DIR)\Vehicle.c.o

	$(CC) $(CFLAGS) -I .\$(BUILD_DIR) $(OBJ_FILES) -o .\IndustryApp.exe

.PHONY: clean
clean:
#	NEED TO UPDATE
	rm -r .\$(BUILD_DIR)
