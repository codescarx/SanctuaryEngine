#ifndef TERRAINSHADER
#define TERRAINSHADER

#include <glm/glm.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"

class TerrainShader : public Shader {
public:
    TerrainShader();
    void loadTerrainData(Terrain *terrain);
    void loadTileIndices(int i, int j);
    void loadMatrices(Camera *camera);
    void loadTessData(const glm::vec2 &screenDim, float tessDivisor);
};

#endif /* TERRAINSHADER */
