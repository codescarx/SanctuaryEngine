#include "Engine.h"

void Engine::update() {
    displayManager.update();
    
    double currentFrameTime = glfwGetTime();
    frameDelta = (currentFrameTime - lastFrameTime) * 1000.f;
    lastFrameTime = currentFrameTime;
}