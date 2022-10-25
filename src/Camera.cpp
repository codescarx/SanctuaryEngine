#include "Camera.h"

#include "Engine.h"
#include "util.h"

Camera::Camera(const glm::vec3 &position, float zNear, float zFar, float fov)
    : position(position), zNear(zNear), zFar(zFar), fov(fov)
{
    update();
}

void Camera::update() {
    move();
    updateMatrices();
}

void Camera::move() {
    DisplayManager *display = Engine::instance->getDisplay();
    float delta = Engine::instance->getDelta();

    if (display->isKeyDown(GLFW_KEY_W)) {
        position.x += speed * delta * sinf(glm::radians(yaw));
        position.z += speed * delta * -cosf(glm::radians(yaw));
    }
    else if (display->isKeyDown(GLFW_KEY_S)) {
        position.x -= speed * delta * sinf(glm::radians(yaw));
        position.z -= speed * delta * -cosf(glm::radians(yaw));
    }
    
    if (display->isKeyDown(GLFW_KEY_A)) {
        yaw -= 45.f * delta;
    } 
    else if (display->isKeyDown(GLFW_KEY_D)) {
        yaw += 45.f * delta;
    }

    if (display->isKeyDown(GLFW_KEY_K)) {
        pitch -= 45.f * delta;
    }
    else if (display->isKeyDown(GLFW_KEY_J)) {
        pitch += 45.f * delta;
    }

    if (display->isKeyDown(GLFW_KEY_SPACE)) {
        position.y += speed * delta;
    }
    else if (display->isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        position.y -= speed * delta;
    }
}

void Camera::updateMatrices() {
    glm::mat4 mat(1.f);
    mat = glm::rotate(mat, glm::radians(pitch), glm::vec3(1.f, 0.f, 0.f));
    mat = glm::rotate(mat, glm::radians(yaw), glm::vec3(0.f, 1.f, 0.f));
    mat = glm::translate(mat, -position);
    viewMatrix = mat;

    float aspect = float(Engine::instance->getDisplay()->getWidth()) / Engine::instance->getDisplay()->getHeight();
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

    vpMatrix = projectionMatrix * viewMatrix;

    invViewMatrix = glm::inverse(viewMatrix);
    invProjectionMatrix = glm::inverse(projectionMatrix);
}
