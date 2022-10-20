#ifndef CAMERA
#define CAMERA

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
    Camera(const glm::vec3 &position, float zNear, float zFar, float fov);
    void update();

    float pitch = 0.f, yaw = 0.f, speed = 50.f;
    glm::vec3 position;

    inline const glm::mat4 &getViewMatrix() const { return viewMatrix; }
    inline const glm::mat4 &getProjectionMatrix() const { return projectionMatrix; }
private:
    void move();
    void updateViewMatrix();
    void updateProjectionMatrix();

    float zNear, zFar, fov;
    glm::mat4 viewMatrix, projectionMatrix;
};

#endif /* CAMERA */
