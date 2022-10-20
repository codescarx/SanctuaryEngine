#include "TerrainShader.h"

#define VERTFILE "res/shader/terrain.vert"
#define TESCFILE "res/shader/terrain.tesc"
#define TESEFILE "res/shader/terrain.tese"
#define FRAGFILE "res/shader/terrain.frag"

static const std::vector<std::string> uniforms = {
    "pos", "tileSize", "vpMatrix"
};

TerrainShader::TerrainShader()
    : Shader(VERTFILE, FRAGFILE, nullptr, TESCFILE, TESEFILE, uniforms) {}

void TerrainShader::loadTileInfo(const glm::vec3 &pos, float tileSize) {
    loadVec3("pos", pos);
    loadFloat("tileSize", tileSize);
}