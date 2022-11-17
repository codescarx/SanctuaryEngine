#include "WaterRenderer.h"

#include "Engine.h"

#define VERTFILE "res/shader/water.vert"
#define TESCFILE "res/shader/terrain.tesc"
#define TESEFILE "res/shader/water.tese"
#define FRAGFILE "res/shader/water.frag"

static const std::vector<std::string> uniforms = {
    "position", "tileSize", "tileCnt", "tiling",
    "viewMatrix", "projectionMatrix", "vpMatrix",
    "screenDim", "tessDivisor",
    "heightScale", "choppiness"
};

WaterRenderer::WaterRenderer() : Shader(VERTFILE, FRAGFILE, nullptr, TESCFILE, TESEFILE, uniforms), dummyVao(new Vao()) {}

void WaterRenderer::render(Scene *scene, Camera *camera) {
    FFTWater *water = scene->water.get();
    if (!water) return;

    use();
    dummyVao->bind();

    loadUniforms(scene, camera);

    water->getHeightmap()->bind(0);
    water->getDxMap()->bind(1);
    water->getDzMap()->bind(2);
    water->getNormalmap()->bind(3);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArraysInstanced(GL_PATCHES, 0, 4, water->tileCnt * water->tileCnt);

    disuse();
    dummyVao->unbind();
}

void WaterRenderer::loadUniforms(Scene *scene, Camera *camera) {
    loadVec3("position", scene->water->position);
    loadFloat("tileSize", scene->water->tileSize);
    loadInt("tileCnt", scene->water->tileCnt);
    loadFloat("tiling", scene->water->tiling);

    loadMat4("viewMatrix", camera->getViewMatrix());
    loadMat4("projectionMatrix", camera->getProjectionMatrix());
    loadMat4("vpMatrix", camera->getVpMatrix());

    loadVec2("screenDim", glm::vec2(Engine::instance->getDisplay()->getWidth(), Engine::instance->getDisplay()->getHeight()));
    loadFloat("tessDivisor", scene->water->tessDivisor);

    loadFloat("heightScale", scene->water->heightScale);
    loadFloat("choppiness", scene->water->choppiness);
}