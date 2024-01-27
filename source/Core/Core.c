// Defines are to ensure only one definition of each function
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include "Core.h"

#include "../GUI/Windows/overview.c"

static void error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}

int main(int argc, char* argv[])
{
    static GLFWwindow *win;
    AppPlatform* platform = calloc(1, sizeof(AppPlatform));
    AppState* current_app_state = loadAppState(0, NULL);

    runAppPlatform(platform, win, current_app_state);

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
        printf("Iteration - %d\n", i);
        processTickAppState(current_app_state);
    }

    printf("Completed Iterations\n");

    closeApp(current_app_state);
    cleanPlatform(platform);
    return 0;
}

void runAppPlatform(AppPlatform* platform, GLFWwindow *win, AppState* current_app_state)
{
    struct nk_glfw glfw = {0};
    platform->width = 0;
    platform->height = 0;
    platform->first_window = calloc(1, sizeof(PopupWindow));
    assignPopupWindowValues(platform->first_window, MAIN_MENU, current_app_state);

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

    while (!glfwWindowShouldClose(win))
    {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame(&glfw);

        /* GUI */
        overview(platform->ctx);
        PopupWindow* window = platform->first_window;
        while(window != NULL)
        {
            drawPopupWindow(window, platform);
            window = window->next;
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
    }

    nk_glfw3_shutdown(&glfw);
    glfwTerminate();
}

int closeApp(AppState* appState)
{
	saveAppState(appState);
    printf("Saved App State\n");
    cleanAppState(appState);
    free(appState);
    printf("Cleaned App State\n");
	return 0;
}

void cleanPlatform(AppPlatform* platform)
{
    PopupWindow* iter = platform->first_window;
    while (iter->next != NULL)
    {
        iter = iter->next;
        free(iter->prev);
    }
    if (iter != NULL)
    {
        free(iter);
    }
    free(platform);
}