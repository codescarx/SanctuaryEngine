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

    scene->terrain = std::move(std::make_unique<Terrain>(glm::vec3(-200.f, 0.f, -200.f), 8, 50.f, 200.f));

    while (!engine.windowShouldClose()) {
        camera->update();
        engine.update(scene, camera);
    }

    delete scene;
    delete camera;

    return 0;
}