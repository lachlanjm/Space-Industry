#ifndef CORE_H
#define CORE_H
/* nuklear - 1.32.0 - public domain */
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

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include "../GUI/includes/nuklear.h"
#include "../GUI/includes/nuklear_glfw_gl3.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

// SELF
#define MAX_MEMORY 4294967295

typedef struct AppPlatform AppPlatform;

#include "..\Simulation\Main\AppState\AppState.h"
#include "..\GUI\Structures\PopupWindow.h"

#define APP_WINDOW_STR "Space Industry"
#define NUMBER_OF_ITERATIONS 100 // TEMPORARY: TBU

struct AppPlatform {
	int width;
	int height;
	uint8_t continue_running;
	struct nk_context *ctx;
	struct nk_colorf bg;
	PopupWindow* first_window;
};

int main(int argc, char* argv[]);

void runAppPlatform(AppPlatform* platform, GLFWwindow *win, AppState* current_app_state);
int closeApp(AppState* appState);
void cleanPlatform(AppPlatform* platform);

#endif