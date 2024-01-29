#ifndef SAVE_APP_STATE_H
#define SAVE_APP_STATE_H

#include ".\AppState.h"

#include <stdio.h>

#define BUF_SIZE 64

enum AttributeTypes {
	APP_STATE_SAVE,
	FACTORY_MANAGER_SAVE,
	FACTORY_SAVE,
	LOGISTICS_CONTRACT_SAVE,
	LOGISTICS_MANAGER_SAVE,
	ORDER_SAVE,
	STOCKPILE_SAVE,
	VEHICLE_SAVE
};

enum WriteType {
	NEW_STRUCT_WRITE,
	ADD_ATTRIBUTE_WRITE,
	BLANK_LINE
};

struct SaveStateQueue {
	struct SaveStateQueue* next;
	enum AttributeTypes type;
	void* data;
};

int saveAppState(AppState* appState, const char* save_file_name);

#endif