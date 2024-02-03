// Defines are to ensure only one definition of each function
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include "Core.h"

// #include "../GUI/includes/overview.c" // FOR DEMO ONLY!!!

static void error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Not enough arguments supplied");
		exit(1);
	}

	static GLFWwindow *win;
	AppPlatform* platform = calloc(1, sizeof(AppPlatform));
	platform->app_dir_path = argv[1];

	runAppPlatform(platform, win);

	/*
	for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
	{
		printf("Iteration - %d\n", i);
		processTickAppState(current_app_state);
	}
	printf("Completed Iterations\n");
	// */

	saveAppState(platform->current_app_state, platform->app_dir_path, "auto_close_save");
	closeApp(platform->current_app_state);
	cleanPlatform(platform);
	printf("Cleaned platform\n\n");
	return 0;
}

void runAppPlatform(AppPlatform* platform, GLFWwindow *win)
{
	struct nk_glfw glfw = {0};
	platform->width = 0;
	platform->height = 0;
	platform->first_window = NULL;
	platform->current_app_state = NULL;

	/* GLFW */
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stdout, "[GFLW] failed to init!\n");
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_WINDOW_STR, NULL, NULL);
	glfwMakeContextCurrent(win);
	glfwGetWindowSize(win, &platform->width, &platform->height);

	/* OpenGL */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to setup GLEW\n");
		exit(1);
	}

	// Font creation/choice (For future: can load cursor here)
	platform->ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);
	{
		struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&glfw, &atlas);
		nk_glfw3_font_stash_end(&glfw);
	}

	platform->bg.r = 0.10f;
	platform->bg.g = 0.18f;
	platform->bg.b = 0.24f;
	platform->bg.a = 1.0f;

	platform->flags = AP_FLAG_LOAD_FILE;

	int secs_btw_proc = 1;
	time_t prev_seconds = NULL; 
	time_t curr_seconds = NULL;
	time(&prev_seconds); 
	while (!glfwWindowShouldClose(win) && !(platform->flags & AP_FLAG_CLOSE))
	{
		if (platform->flags & AP_FLAG_RUN_SIMULATION)
		{
			time(&curr_seconds);
			if (curr_seconds - prev_seconds >= secs_btw_proc)
			{
				processTickAppState(platform->current_app_state);
				time(&prev_seconds);
			}
		}

		/* Input */
		glfwPollEvents();
		nk_glfw3_new_frame(&glfw);

		/* GUI */
		// overview(platform->ctx); // !!!!!!!!!!!!!!!!!!!!!!! FOR DEMO ONLY
		if (platform->flags & AP_FLAG_SAVE_STATE)
		{
			drawSaveFileMenu(platform, "Save File Window");
		}
		else if (platform->flags & AP_FLAG_LOAD_FILE)
		{
			drawLoadFileMenu(platform, "Load File Window");
		}
		else
		{
			PopupWindow* window = platform->first_window;
			while(window != NULL)
			{
				if (!nk_window_is_hidden(platform->ctx, window->name) || !nk_window_find(platform->ctx, window->name))
				{
					drawPopupWindow(window, platform);
				}
				else
				{
					window = window->prev;
					removePopupWindow(window->next);
				}
				
				window = window->next;
			}
		}

		/* Draw */
		glfwGetWindowSize(win, &platform->width, &platform->height);
		glViewport(0, 0, platform->width, platform->height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(platform->bg.r, platform->bg.g, platform->bg.b, platform->bg.a);
		/* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
		 * with blending, scissor, face culling, depth test and viewport and
		 * defaults everything back into a default state.
		 * Make sure to either a.) save and restore or b.) reset your own state after
		 * rendering the UI. */
		nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		glfwSwapBuffers(win);
		fflush(stdout);
	}

	nk_glfw3_shutdown(&glfw);
	glfwTerminate();
}

void clearPopupWindows(AppPlatform* platform)
{
	if (platform == NULL) return;
	PopupWindow* iter = platform->first_window;
	if (iter != NULL)
	{
		while (iter->next != NULL)
		{
			iter = iter->next;
			free(iter->prev);
		}
		free(iter);
	}
}

void resetPlatform(AppPlatform* platform)
{
	clearPopupWindows(platform);
	platform->first_window = calloc(1, sizeof(PopupWindow));
	assignPopupWindowValues(platform->first_window, MAIN_MENU, platform->current_app_state);
	addNewPopupWindow(platform->first_window, SIMULATION_CONTROL_MENU, NULL);
}

int closeApp(AppState* appState)
{
	printf("Saved App State\n");
	cleanAppState(appState);
	free(appState);
	printf("Cleaned App State\n");
	return 0;
}

void cleanPlatform(AppPlatform* platform)
{
	clearPopupWindows(platform);
	free(platform);
}