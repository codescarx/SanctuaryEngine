#ifndef ENGINE
#define ENGINE

#include "DisplayManager.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "WaterRenderer.h"
#include "Scene.h"
#include "Fbo.h"
#include "Deferred.h"

class Engine {
public:
    Engine(int width, int height, const char *title);
    ~Engine();
    inline bool windowShouldClose() { return displayManager.windowShouldClose(); };
    void update(Scene *scene, Camera *camera);
    inline DisplayManager* getDisplay() { return &displayManager; }
    inline float getDelta() { return frameDelta; }
    static Engine *instance;

    void onWindowSizeChanged(int newWidth, int newHeight);
private:
    DisplayManager displayManager;
    EntityRenderer entityRenderer;
    TerrainRenderer terrainRenderer;
    WaterRenderer waterRenderer;
    Deferred deferredProcessor;
    double lastFrameTime = 0.0;
    float frameDelta = 0.f;
    Fbo *gBuffer, *waterFbo;
};

#endif /* ENGINE */
