#include "Entity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

void Entity::updateTransformationMatrix() {
    glm::mat4 &mat = transformationMatrix;
    mat = glm::mat4(1.f);
    mat = glm::translate(mat, position);
    mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    mat = glm::scale(mat, scale);
}