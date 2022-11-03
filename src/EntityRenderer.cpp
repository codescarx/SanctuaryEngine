#include "EntityRenderer.h"

#define VERTFILE "res/shader/entity.vert"
#define FRAGFILE "res/shader/entity.frag"

const std::vector<std::string> uniforms = {
    "transformationMatrix", "vpMatrix"
};

EntityRenderer::EntityRenderer()
    : Shader(VERTFILE, FRAGFILE, nullptr, nullptr, nullptr, uniforms) {}

void EntityRenderer::render(Scene *scene, Camera *camera) {
    use();

    loadMat4("vpMatrix", camera->getVpMatrix());
    for (Entity &e : scene->entities) {
        e.model.mesh->bind();
        e.model.texture->bind(0);
        if (e.model.cullBackface) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);
        
        e.updateTransformationMatrix();
        loadMat4("transformationMatrix", e.getTransformationMatrix());
        glDrawArrays(GL_TRIANGLES, 0, e.model.mesh->numVertices);

        e.model.mesh->unbind();
    }

    disuse();
}