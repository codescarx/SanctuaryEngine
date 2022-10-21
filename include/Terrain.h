#ifndef TERRAIN
#define TERRAIN

#include <glm/glm.hpp>
#include "Texture.h"
#include "Heightmap.h"

class Terrain {
public:
    Terrain(const glm::vec3 &position, int tileCnt, float tileSize, float tessDivisor, Texture *texture, float textureTiling, Heightmap *heightmap)
        : position(position), tileCnt(tileCnt), tileSize(tileSize), tessDivisor(tessDivisor), texture(texture), textureTiling(textureTiling), heightmap(heightmap) {};
    const glm::vec3 position;
    const int tileCnt;
    const float tileSize;
    float tessDivisor;
    Texture *texture;
    Heightmap *heightmap;
    float textureTiling;
};

#endif /* TERRAIN */
