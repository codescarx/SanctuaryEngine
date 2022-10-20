#ifndef TERRAIN
#define TERRAIN

#include <glm/glm.hpp>

class Terrain {
public:
    Terrain(const glm::vec3 &position, int tileCnt, float tileSize)
        : position(position), tileCnt(tileCnt), tileSize(tileSize) {};
    const glm::vec3 position;
    const int tileCnt;
    const float tileSize;
};

#endif /* TERRAIN */
