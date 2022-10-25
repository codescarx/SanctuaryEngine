#ifndef SCENE
#define SCENE

#include <glm/glm.hpp>
#include <memory>

#include "Terrain.h"

class Scene {
public:
    std::unique_ptr<Terrain> terrain;
    glm::vec3 lightDirection, lightColour;
    float ambientLight = 0.1f;
};

#endif /* SCENE */
