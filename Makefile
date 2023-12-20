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

ENV_DIR := Environment
MAIN_DIR := Main
MAN_DIR := Management
MAR_DIR := Markets
PRO_DIR := Production
TRA_DIR := Transport

CFLAGS := -Wall -O3 -I $(SRC_DIR:%=.\%)


.PHONY: all
all:
#	mkdir .\$(BUILD_DIR)
#	mkdir .\$(BUILD_DIR)\$(ENV_DIR)
#	mkdir .\$(BUILD_DIR)\$(MAIN_DIR)
#	mkdir .\$(BUILD_DIR)\$(MAN_DIR)
#	mkdir .\$(BUILD_DIR)\$(MAR_DIR)
#	mkdir .\$(BUILD_DIR)\$(PRO_DIR)
#	mkdir .\$(BUILD_DIR)\$(TRA_DIR)

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Enums\TransportConnectionType.c -o .\$(BUILD_DIR)\$(ENV_DIR)\TransportConnectionType.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Enums\TransportNode.c -o .\$(BUILD_DIR)\$(ENV_DIR)\TransportNode.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Structures\Map.c -o .\$(BUILD_DIR)\$(ENV_DIR)\Map.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(ENV_DIR)\Structures\MarketMap.c -o .\$(BUILD_DIR)\$(ENV_DIR)\MarketMap.c.o

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAIN_DIR)\AppState.c -o .\$(BUILD_DIR)\$(MAIN_DIR)\AppState.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAIN_DIR)\SaveAppState.c -o .\$(BUILD_DIR)\$(MAIN_DIR)\SaveAppState.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAIN_DIR)\LoadAppState.c -o .\$(BUILD_DIR)\$(MAIN_DIR)\LoadAppState.c.o

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAN_DIR)\Logistics\LogisticsContract.c -o .\$(BUILD_DIR)\$(MAN_DIR)\LogisticsContract.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAN_DIR)\Logistics\LogisticsManager.c -o .\$(BUILD_DIR)\$(MAN_DIR)\LogisticsManager.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAN_DIR)\Production\FactoryManager.c -o .\$(BUILD_DIR)\$(MAN_DIR)\FactoryManager.c.o
	
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAR_DIR)\Structures\Order.c -o .\$(BUILD_DIR)\$(MAR_DIR)\Order.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(MAR_DIR)\Structures\ProductMarket.c -o .\$(BUILD_DIR)\$(MAR_DIR)\ProductMarket.c.o

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Enums\Product.c -o .\$(BUILD_DIR)\$(PRO_DIR)\Product.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Enums\ProductionRecipe.c -o .\$(BUILD_DIR)\$(PRO_DIR)\ProductionRecipe.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Structures\Factory.c -o .\$(BUILD_DIR)\$(PRO_DIR)\Factory.c.o
	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(PRO_DIR)\Structures\Stockpile.c -o .\$(BUILD_DIR)\$(PRO_DIR)\Stockpile.c.o

	$(CC) $(CFLAGS) -c .\$(SRC_DIR)\$(TRA_DIR)\Structures\Vehicle.c -o .\$(BUILD_DIR)\$(TRA_DIR)\Vehicle.c.o

.PHONY: clean
clean:
#	NEED TO UPDATE
	rm -r .\$(BUILD_DIR)
