#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include <GLFW/glfw3.h>

class DisplayManager {
public:
    DisplayManager(int width, int height, const char *title);
    ~DisplayManager();
    void update();
    inline bool windowShouldClose() { return glfwWindowShouldClose(window); }
private:
    int width, height;
    const char *title;
    GLFWwindow *window;
};

#endif /* DISPLAYMANAGER */
