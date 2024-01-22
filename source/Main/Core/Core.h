#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES // Current work around for static assert neg array size issue
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR // For font atlas
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING // Used for font handling
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "..\..\GUI\nuklear.h"
#include "..\..\GUI\nuklear_glfw_gl4.h"

// SELF
#define MAX_MEMORY 4294967295

#include "..\AppState\AppState.h"

#define NUMBER_OF_ITERATIONS 1000 // TEMPORARY: TBU

int main(int argc, char* argv[]);

int closeApp(AppState* appState);

#endif