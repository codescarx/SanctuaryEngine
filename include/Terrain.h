#ifndef TERRAIN
#define TERRAIN

#include <glm/glm.hpp>
#include "Texture.h"

class Terrain {
public:
    Terrain(const glm::vec3 &position, int tileCnt, float tileSize, float tessDivisor, Texture *texture)
        : position(position), tileCnt(tileCnt), tileSize(tileSize), tessDivisor(tessDivisor), texture(texture) {};
    const glm::vec3 position;
    const int tileCnt;
    const float tileSize;
    float tessDivisor;
    Texture *texture;
};

#endif /* TERRAIN */
