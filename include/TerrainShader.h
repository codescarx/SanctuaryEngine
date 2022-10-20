#ifndef TERRAINSHADER
#define TERRAINSHADER

#include <glm/glm.hpp>
#include "Shader.h"

class TerrainShader : public Shader {
public:
    TerrainShader();
    void loadTileInfo(const glm::vec3 &pos, float tileSize);
    inline void loadVpMatrix(const glm::mat4 &m) {
        loadMat4("vpMatrix", m);
    }
};

#endif /* TERRAINSHADER */
