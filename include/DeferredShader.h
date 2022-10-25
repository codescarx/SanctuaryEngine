#ifndef DEFERREDSHADER
#define DEFERREDSHADER

#include "Shader.h"
#include "Scene.h"
#include "Camera.h"

class DeferredShader : public Shader {
public:
    DeferredShader();
    void loadData(Scene *scene, Camera *camera);
};

#endif /* DEFERREDSHADER */
