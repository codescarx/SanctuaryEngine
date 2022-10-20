#ifndef ENGINE
#define ENGINE

#include "DisplayManager.h"

class Engine {
public:
    Engine(int width, int height, const char *title) : displayManager(width, height, title) {};
    inline bool windowShouldClose() { return displayManager.windowShouldClose(); };
    void update();
    inline DisplayManager& getDisplay() { return displayManager; }
private:
    DisplayManager displayManager;
};

#endif /* ENGINE */
