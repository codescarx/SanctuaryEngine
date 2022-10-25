#ifndef DEFERRED
#define DEFERRED

#include "Vao.h"
#include "Fbo.h"
#include "Scene.h"
#include "DeferredShader.h"

class Deferred {
public:
    void doDeferredShading(Scene *scene, Fbo *deferredFbo);
private:
    DeferredShader shader;
    Vao * const dummyVao = new Vao();
};

#endif /* DEFERRED */
