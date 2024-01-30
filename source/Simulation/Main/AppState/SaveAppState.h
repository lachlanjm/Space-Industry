#ifndef SAVE_APP_STATE_H
#define SAVE_APP_STATE_H

#include ".\AppState.h"
#include "..\..\..\Helpers\SaveFileStandards.h"

#include <stdio.h>

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