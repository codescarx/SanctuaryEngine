#ifndef DEFERREDSHADER
#define DEFERREDSHADER

#include "Shader.h"
#include "Scene.h"

class DeferredShader : public Shader {
public:
    DeferredShader();
    void loadSceneData(Scene *scene);
};

#endif /* DEFERREDSHADER */
