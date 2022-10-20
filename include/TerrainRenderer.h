#ifndef TERRAINRENDERER
#define TERRAINRENDERER

#include "TerrainShader.h"
#include "Scene.h"
#include "Camera.h"
#include "Vao.h"

class TerrainRenderer {
public:
    TerrainRenderer() : dummyVao(new Vao()) {};
    void render(Scene *scene, Camera *camera);
private:
    TerrainShader shader;
    Vao *dummyVao;
};

#endif /* TERRAINRENDERER */
