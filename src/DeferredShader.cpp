#include "DeferredShader.h"

#define VERTFILE "res/shader/deferred.vert"
#define FRAGFILE "res/shader/deferred.frag"

static const std::vector<std::string> uniforms = {
    "invViewMatrix", "invProjectionMatrix",
    "lightDirection", "lightColour", "cameraPos", "ambientLight",
    "fogDensity", "fogGradient",

    "waterLevel", "A", "tiling", "waterColour"
};

DeferredShader::DeferredShader()
    : Shader(VERTFILE, FRAGFILE, nullptr, nullptr, nullptr, uniforms) {}

void DeferredShader::loadData(Scene *scene, Camera *camera) {
    loadMat4("invViewMatrix", camera->getInvViewMatrix());
    loadMat4("invProjectionMatrix", camera->getInvProjectionMatrix());
    loadVec3("lightDirection", glm::normalize(scene->lightDirection));
    loadVec3("lightColour", scene->lightColour);
    loadVec3("cameraPos", camera->position);
    loadFloat("ambientLight", scene->ambientLight);
    loadFloat("fogDensity", scene->fogDensity);
    loadFloat("fogGradient", scene->fogGradient);

    loadFloat("waterLevel", scene->water->position.y);
    loadFloat("A", scene->water->A);
    loadFloat("tiling", scene->water->tiling);
    loadVec3("waterColour", scene->water->colour);
}