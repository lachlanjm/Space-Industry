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

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

// SELF
#define MAX_MEMORY 4294967295

typedef struct AppPlatform AppPlatform;
typedef enum AppTickRate AppTickRate;

#include "..\Simulation\Main\AppState\AppState.h"
#include "..\GUI\Structures\PopupWindow.h"
#include "..\GUI\Windows\LoadFileMenu.h"
#include "..\GUI\Windows\SaveFileMenu.h"

#define APP_WINDOW_STR "Space Industry"

// min. ms between ticks
enum AppTickRate {
	AP_VERY_SLOW = 1000,
	AP_SLOW = 500,
	AP_NORMAL = 250,
	AP_FAST = 100,
	AP_VERY_FAST = 20,
	AP_MAX = 0
};

enum AppPlatformFlags {
	AP_FLAG_LOAD_FILE = 1,
	AP_FLAG_SAVE_STATE = 2,
	AP_FLAG_RUN_SIMULATION = 4,
	AP_FLAG_CLOSE = 8
};

struct NewWindowInfo {
	float parent_x;
	float parent_y;
	float parent_w;
	float parent_h;
	float child_x;
	float child_y;
	float child_w;
	float child_h;
};

struct AppPlatform {
	int width;
	int height;

	uint8_t flags;
	struct nk_colorf bg;
	struct nk_context *ctx;
	char* app_dir_path;

	struct NewWindowInfo new_win_info;

	PopupWindow* first_window;
	AppState* current_app_state;
	AppTickRate tick_time;
};

int main(int argc, char* argv[]);

void setParentDimensions(AppPlatform* const platform, const float parent_x, const float parent_y, const float parent_w, const float parent_h);
void calcChildPosition(AppPlatform* const platform, const float child_w, const float child_h);

void runAppPlatform(AppPlatform* platform, GLFWwindow *win);
void clearPopupWindows(AppPlatform* platform);
void resetPlatform(AppPlatform* platform);
int closeApp(AppState* appState);
void cleanPlatform(AppPlatform* platform);

#endif