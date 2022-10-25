#include "DeferredShader.h"

#define VERTFILE "res/shader/deferred.vert"
#define FRAGFILE "res/shader/deferred.frag"

static const std::vector<std::string> uniforms = {
    
};

DeferredShader::DeferredShader()
    : Shader(VERTFILE, FRAGFILE, nullptr, nullptr, nullptr, uniforms) {}

void DeferredShader::loadSceneData(Scene *scene) {

}