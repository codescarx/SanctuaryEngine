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
    float zNear, zFar, fov;
    glm::vec3 position;

    inline const glm::mat4 &getViewMatrix() const { return viewMatrix; }
    inline const glm::mat4 &getProjectionMatrix() const { return projectionMatrix; }
    inline const glm::mat4 &getVpMatrix() const { return vpMatrix; }
private:
    void move();
    void updateMatrices();

    glm::mat4 viewMatrix, projectionMatrix, vpMatrix;
};

#endif /* CAMERA */
