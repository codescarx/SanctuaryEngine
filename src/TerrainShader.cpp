#include "TerrainShader.h"

#define VERTFILE "res/shader/terrain.vert"
#define TESCFILE "res/shader/terrain.tesc"
#define TESEFILE "res/shader/terrain.tese"
#define FRAGFILE "res/shader/terrain.frag"

static const std::vector<std::string> uniforms = {
    "position", "tileSize", "tileCnt", "textureTiling", "i", "j",
    "viewMatrix", "projectionMatrix", "vpMatrix",
    "screenDim", "tessDivisor"
};

TerrainShader::TerrainShader()
    : Shader(VERTFILE, FRAGFILE, nullptr, TESCFILE, TESEFILE, uniforms) {}

void TerrainShader::loadTerrainData(Terrain *terrain) {
    loadVec3("position", terrain->position);
    loadFloat("tileSize", terrain->tileSize);
    loadInt("tileCnt", terrain->tileCnt);
    loadFloat("textureTiling", terrain->textureTiling);
}

void TerrainShader::loadTileIndices(int i, int j) {
    loadInt("i", i);
    loadInt("j", j);
}

void TerrainShader::loadMatrices(Camera *camera) {
    loadMat4("viewMatrix", camera->getViewMatrix());
    loadMat4("projectionMatrix", camera->getProjectionMatrix());
    loadMat4("vpMatrix", camera->getVpMatrix());
}

void TerrainShader::loadTessData(const glm::vec2 &screenDim, float tessDivisor) {
    loadVec2("screenDim", screenDim);
    loadFloat("tessDivisor", tessDivisor);
}