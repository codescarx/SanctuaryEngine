#include <GL/glew.h>
#include "DisplayManager.h"
#include "util.h"

DisplayManager::DisplayManager(int width, int height, const char *title) : width(width), height(height), title(title) {
    if (!glfwInit()) {
        fatal("glfw initialization failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) fatal("failed to glfwCreateWindow");
    
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) fatal("glewInit is not OK");
    glfwSwapInterval(1);
}

void DisplayManager::update() {
    glViewport(0, 0, width, height);
    glfwPollEvents();
    glfwSwapBuffers(window);
}

DisplayManager::~DisplayManager() {
    glfwDestroyWindow(window);
    glfwTerminate();
}