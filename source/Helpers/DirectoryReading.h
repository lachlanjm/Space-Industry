#ifndef DIRECTORY_READING_H
#define DIRECTORY_READING_H

#include <stdio.h>

#ifdef _WIN64  // windows platform
	#include <windows.h>
#else
	#include <dirent.h>
#endif

typedef enum DirPtrStatus
{
	DIR_PTR_UNINITIALISED,
	DIR_PTR_INITIALISED,
	DIR_PTR_OPEN,
	DIR_PTR_CLOSED
} DirPtrStatus;

#ifdef _WIN64  // windows platform
	typedef struct DirPtr
	{
		DirPtrStatus status;
		char* dir_path;
		HANDLE handle;
		WIN32_FIND_DATA FindFileData;
	} DirPtr;
#else
	typedef struct DirPtr
	{
		DirPtrStatus status;
		char* dir_path;
		DIR* dir_ptr_backend;
		struct dirent *de;
	} DirPtr;
#endif


DirPtr* newDirPtr();
char* currentPath(DirPtr* ptr);
int openDir(DirPtr* ptr, char* dir_path);
int getNextFile(DirPtr* ptr, char* file_name_buffer);
int closeDir(DirPtr* ptr); // Frees the ptr memory as well

#endif