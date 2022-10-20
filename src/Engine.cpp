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

void Engine::update() {
    displayManager.update();
    
    double currentFrameTime = glfwGetTime();
    frameDelta = (currentFrameTime - lastFrameTime) * 1000.f;
    lastFrameTime = currentFrameTime;
}