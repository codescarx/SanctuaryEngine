#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include <GLFW/glfw3.h>

class DisplayManager {
public:
    DisplayManager(int width, int height, const char *title);
    ~DisplayManager();
    void update();
    inline bool windowShouldClose() { return glfwWindowShouldClose(window); }
    inline bool isKeyDown(int key) { return glfwGetKey(window, key) == GLFW_PRESS; }
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
private:
    int width, height;
    const char *title;
    GLFWwindow *window;
};

#endif /* DISPLAYMANAGER */
