#include "TerrainRenderer.h"

#include "Engine.h"

void TerrainRenderer::render(Scene *scene, Camera *camera) {
    Terrain *terrain = scene->terrain.get();
    if (!terrain) return;
    
    shader.use();
    dummyVao->bind();

    shader.loadMatrices(camera);
    shader.loadTessData(glm::vec2(Engine::instance->getDisplay()->getWidth(), Engine::instance->getDisplay()->getHeight()), terrain->tessDivisor);

    for (int i = 0; i < terrain->tileCnt; i++) {
        for (int j = 0; j < terrain->tileCnt; j++) {
            glm::vec3 pos = glm::vec3(
                terrain->position.x + terrain->tileSize * i,
                terrain->position.y,
                terrain->position.z + terrain->tileSize * j
            );
            shader.loadTileInfo(pos, terrain->tileSize);

            glPatchParameteri(GL_PATCH_VERTICES, 4);
            glDrawArrays(GL_PATCHES, 0, 4);
        }
    }

    shader.disuse();
    dummyVao->unbind();
}