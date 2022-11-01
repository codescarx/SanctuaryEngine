#ifndef ENTITYRENDERER
#define ENTITYRENDERER

#include "Scene.h"
#include "Camera.h"
#include "Shader.h"

class EntityRenderer : Shader {
public:
    void render(Scene *scene, Camera *camera);
private:
    
};


#endif /* ENTITYRENDERER */
