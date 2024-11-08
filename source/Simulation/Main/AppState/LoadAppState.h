#ifndef LOAD_APP_STATE_H
#define LOAD_APP_STATE_H

#include ".\AppState.h"
#include "..\..\..\Helpers\SaveFileStandards.h"
#include "..\..\..\Helpers\DirectoryReading.h"

#include <stdio.h>

struct LoadStateIdList {
	struct LoadStateIdList* next;
	int id; // Key
	void* data; // Value
};

AppState* loadAppState(const char* app_dir_path, const char* save_file_name);

#endif