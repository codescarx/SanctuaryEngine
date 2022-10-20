#include "Camera.h"

#include "Engine.h"

Camera::Camera(const glm::vec3 &position, float zNear, float zFar, float fov)
    : position(position), zNear(zNear), zFar(zFar), fov(fov)
{
    update();
}

void Camera::update() {
    direction.x = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
    direction.y = sinf(glm::radians(pitch));
    direction.z = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));
    direction = glm::normalize(direction);

    move();

    updateViewMatrix();
    updateProjectionMatrix();
}

void Camera::move() {
    DisplayManager *display = Engine::instance->getDisplay();
    float delta = Engine::instance->getDelta();
    if (display->isKeyDown(GLFW_KEY_W)) {
        position += speed * delta * direction;
    }
    else if (display->isKeyDown(GLFW_KEY_S)) {
        position -= speed * delta * direction;
    }
    
    if (display->isKeyDown(GLFW_KEY_A)) {
        yaw -= 45.f * delta;
    } 
    else if (display->isKeyDown(GLFW_KEY_D)) {
        yaw += 45.f * delta;
    }

    if (display->isKeyDown(GLFW_KEY_R)) {
        pitch += 45.f * delta;
    }
    else if (display->isKeyDown(GLFW_KEY_F)) {
        pitch -= 45.f * delta;
    }
}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0.f, 1.f, 0.f));
}

void Camera::updateProjectionMatrix() {
    float aspect = float(Engine::instance->getDisplay()->getWidth()) / Engine::instance->getDisplay()->getHeight();
    projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
}