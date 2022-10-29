#include "Engine.h"
#include "util.h"
#include <iostream>

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

int main(void) {
    
    Engine engine(1920, 1080, "Engine Demo");
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );

    Scene *scene = new Scene();
    Camera *camera = new Camera(glm::vec3(0.f, 10.f, 0.f), 1.f, 1000.f, 50.f);

    scene->fogDensity = 0.003f;
    scene->lightDirection = glm::vec3(0, -1, -1);
    scene->lightColour = glm::vec3(1.0f);
    scene->ambientLight = 0.4f;
    scene->terrain = std::move(std::make_unique<Terrain>(glm::vec3(-400.f, 0.f, -400.f), 16, 50.f, 100.f, new Texture("res/sand.jpg"), 50.f, new Heightmap("res/heightmap.png", 100.f, 10.f)));
    scene->skyboxTexture = new Texture({"res/skybox/posx.png","res/skybox/negx.png","res/skybox/posy.png","res/skybox/negy.png","res/skybox/posz.png","res/skybox/negz.png"});

    scene->water = std::move(std::make_unique<FFTWater>(512, 200.f, 26.f, 1000.f, glm::vec2(1, 0), 0.5f));
    scene->water->position = glm::vec3(0.f);
    scene->water->tiling = 0.02f;

    while (!engine.windowShouldClose()) {
        camera->update();
        scene->water->update();
        engine.update(scene, camera);
    }

    delete scene;
    delete camera;

    return 0;
}