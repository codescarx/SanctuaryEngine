#include "Engine.h"

#include "util.h"

Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const char *title) : displayManager(width, height, title) {
    if (instance) fatal("tried to make multiple instances of Engine");
    instance = this;
}

Engine::~Engine() {
    instance = nullptr;
}

void Engine::update(Scene *scene, Camera *camera) {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (displayManager.isKeyDown(GLFW_KEY_F3)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    terrainRenderer.render(scene, camera);

    displayManager.update();
    
    double currentFrameTime = glfwGetTime();
    frameDelta = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}