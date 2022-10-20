#ifndef TERRAINSHADER
#define TERRAINSHADER

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"

class TerrainShader : public Shader {
public:
    TerrainShader();
    void loadTileInfo(const glm::vec3 &pos, float tileSize);
    void loadMatrices(Camera *camera);
    void loadTessData(const glm::vec2 &screenDim, float tessDivisor);
};

#endif /* TERRAINSHADER */
