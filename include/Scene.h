#ifndef SCENE
#define SCENE

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Entity.h"
#include "Terrain.h"
#include "FFTWater.h"
#include "Texture.h"

class Scene {
public:
    std::vector<Entity> entities;
    std::unique_ptr<Terrain> terrain = nullptr;
    std::unique_ptr<FFTWater> water = nullptr;
    glm::vec3 lightDirection, lightColour;
    float ambientLight = 0.1f, fogDensity = 0.004f, fogGradient = 2.0f;
    Texture *skyboxTexture = nullptr;
};

#endif /* SCENE */
