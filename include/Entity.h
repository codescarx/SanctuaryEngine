#ifndef ENTITY
#define ENTITY

#include <glm/vec3.hpp>

#include "Vao.h"
#include "Texture.h"

struct Model {
    Vao * const mesh;
    Texture * const texture;
};

class Entity {
public:
    Entity(const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &scale, const Model &model)
        : position(pos), rotation(rot), scale(scale), model(model) {}
    glm::vec3 position, rotation, scale;
    const Model model;
    void updateTransformationMatrix();
    inline const glm::mat4& getTransformationMatrix() const { return transformationMatrix; }
private:
    glm::mat4 transformationMatrix;
};

#endif /* ENTITY */
