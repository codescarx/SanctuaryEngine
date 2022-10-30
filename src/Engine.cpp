#include "Engine.h"

#include "util.h"

Engine* Engine::instance = nullptr;

Engine::Engine(int width, int height, const char *title) : displayManager(width, height, title) {
    if (instance) fatal("tried to make multiple instances of Engine");
    instance = this;
    gBuffer = new Fbo(displayManager.getWidth(), displayManager.getHeight(), {GL_RGBA8, GL_RGBA32F, GL_RGBA32F}, true);
    waterFbo = new Fbo(displayManager.getWidth(), displayManager.getHeight(), {GL_RGBA32F}, true);
}

Engine::~Engine() {
    instance = nullptr;
}

void Engine::update(Scene *scene, Camera *camera) {

    if (displayManager.isKeyDown(GLFW_KEY_F3)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    gBuffer->bindToDraw();
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    terrainRenderer.render(scene, camera);
    gBuffer->unbind();

    waterFbo->bindToDraw();
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    waterRenderer.render(scene, camera);
    waterFbo->unbind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    deferredProcessor.doDeferredShading(scene, camera, gBuffer, waterFbo);

    displayManager.update();
    
    double currentFrameTime = glfwGetTime();
    frameDelta = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

void Engine::onWindowSizeChanged(int newWidth, int newHeight) {
    gBuffer->resize(newWidth, newHeight);
    waterFbo->resize(newWidth, newHeight);
}