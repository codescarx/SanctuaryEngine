#include "TerrainRenderer.h"

#include "Engine.h"

void TerrainRenderer::render(Scene *scene, Camera *camera) {
    Terrain *terrain = scene->terrain.get();
    if (!terrain) return;
    
    shader.use();
    dummyVao->bind();

    shader.loadTerrainData(terrain);
    shader.loadMatrices(camera);
    shader.loadTessData(glm::vec2(Engine::instance->getDisplay()->getWidth(), Engine::instance->getDisplay()->getHeight()), terrain->tessDivisor);
    terrain->texture->bind(0);

    for (int i = 0; i < terrain->tileCnt; i++) {
        for (int j = 0; j < terrain->tileCnt; j++) {
            shader.loadTileIndices(i, j);
            glPatchParameteri(GL_PATCH_VERTICES, 4);
            glDrawArrays(GL_PATCHES, 0, 4);
        }
    }

    shader.disuse();
    dummyVao->unbind();
}