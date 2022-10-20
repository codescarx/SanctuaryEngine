#ifndef TERRAIN
#define TERRAIN

#include <glm/glm.hpp>

class Terrain {
public:
    Terrain(const glm::vec3 &position, int tileCnt, float tileSize, float tessDivisor)
        : position(position), tileCnt(tileCnt), tileSize(tileSize), tessDivisor(tessDivisor) {};
    const glm::vec3 position;
    const int tileCnt;
    const float tileSize;
    float tessDivisor;
};

#endif /* TERRAIN */
