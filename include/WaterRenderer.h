#ifndef WATERRENDERER
#define WATERRENDERER

#include "Shader.h"

#include "Scene.h"
#include "Camera.h"
#include "Vao.h"

class WaterRenderer : public Shader {
public:
    WaterRenderer();
    void render(Scene *scene, Camera *camera);
private:
    Vao *dummyVao;
    void loadUniforms(Scene *scene, Camera *camera);
};

#endif /* WATERRENDERER */
