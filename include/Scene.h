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
    float ambientLight = 0.1f, fogDensity = 0.007f, fogGradient = 1.5f;
    Texture *skyboxTexture = nullptr;
};

#endif /* SCENE */
