#ifndef CAMERA
#define CAMERA

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
    Camera(const glm::vec3 &position, float zNear, float zFar, float fov);
    void update();

    float pitch = 0.f, yaw = 0.f, speed = 10.f;
    glm::vec3 position;
private:
    void move();
    void updateViewMatrix();
    void updateProjectionMatrix();

    float zNear, zFar, fov;
    glm::vec3 direction;
    glm::mat4 viewMatrix, projectionMatrix;
};

#endif /* CAMERA */
