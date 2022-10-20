#ifndef ENGINE
#define ENGINE

#include "DisplayManager.h"
#include "TerrainRenderer.h"
#include "Scene.h"

class Engine {
public:
    Engine(int width, int height, const char *title);
    ~Engine();
    inline bool windowShouldClose() { return displayManager.windowShouldClose(); };
    void update(Scene *scene, Camera *camera);
    inline DisplayManager* getDisplay() { return &displayManager; }
    inline float getDelta() { return frameDelta; }
    static Engine *instance;
private:
    DisplayManager displayManager;
    TerrainRenderer terrainRenderer;
    double lastFrameTime = 0.0;
    float frameDelta = 0.f;
};

#endif /* ENGINE */
