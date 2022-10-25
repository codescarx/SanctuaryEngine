#ifndef SCENE
#define SCENE

#include <glm/glm.hpp>
#include <memory>

#include "Terrain.h"
#include "Texture.h"

class Scene {
public:
    std::unique_ptr<Terrain> terrain;
    glm::vec3 lightDirection, lightColour;
    float ambientLight = 0.1f, fogDensity = 0.004f, fogGradient = 2.0f;
    Texture *skyboxTexture = nullptr;
};

#endif /* SCENE */
