#include "Engine.h"
#include "util.h"
#include <iostream>
#include <imgui/imgui.h>

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
    Camera *camera = new Camera(glm::vec3(0.f, 50.f, 0.f), 1.f, 2000.f, 50.f);

    scene->fogDensity = 0.003f;
    scene->lightDirection = glm::vec3(0, -1, 0.7);
    scene->lightColour = glm::vec3(1.0f);
    scene->ambientLight = 0.4f;
    scene->skyboxTexture = new Texture({"res/skybox/posx.png","res/skybox/negx.png","res/skybox/posy.png","res/skybox/negy.png","res/skybox/posz.png","res/skybox/negz.png"});

    // scene->terrain = std::move(std::make_unique<Terrain>(glm::vec3(-400.f, 0.f, -400.f), 16, 50.f, 50.f, new Texture("res/sand.jpg"), 50.f, new Heightmap("res/heightmap.png", 100.f, 5.f)));

    // scene->water = std::move(std::make_unique<FFTWater>(512, 200.f, 26.f, 1000.f, glm::vec2(0, 1), 0.5f));
    // scene->water->position = glm::vec3(-800.f, 0.f, -800.f);
    // scene->water->tiling = 20.f;
    // scene->water->fadeSpeed = 0.09f;

    Model monkey(Vao::loadFromObj("res/monkey.obj"), new Texture(0.5f, 0.5f, 0.5f));
    Model leaves(Vao::loadFromObj("res/spruce_05_LOD0.obj", 1), new Texture("res/spruceleaf.png"));
    Model trunk(Vao::loadFromObj("res/spruce_05_LOD0.obj", 0), new Texture("res/sprucebark.png"));
    leaves.cullBackface = trunk.cullBackface = false;

    scene->entities.emplace_back(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), trunk);
    scene->entities.emplace_back(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(1.f), leaves);

    while (!engine.windowShouldClose()) {
        camera->update();

        if (scene->water) scene->water->update();

        // ImGui::Begin("options");

        // ImGui::SliderFloat("lx", &scene->lightDirection.x, -1, 1);
        // ImGui::SliderFloat("ly", &scene->lightDirection.y, -1, 1);
        // ImGui::SliderFloat("lz", &scene->lightDirection.z, -1, 1);
        
        // ImGui::SliderFloat("fade", &scene->water->fadeSpeed, 0, 1);
        // ImGui::SliderFloat("y", &scene->water->position.y, -20, 20);
        // ImGui::SliderFloat("normal", &scene->water->normalStrength, 0.1, 2.0);
        // ImGui::SliderFloat("reflectivity", &scene->water->reflectivity, 0.1, 5.0);
        // ImGui::SliderFloat("shineDamper", &scene->water->shineDamper, 50.0, 300.0);
        // ImGui::End();

        // ImGui::Begin("Ocean Heightmap");
        // ImGui::Image((void*)(intptr_t)scene->water->getHeightmap()->textureId, ImVec2(512, 512));
        // ImGui::End();

        engine.update(scene, camera);
    }

    delete scene;
    delete camera;

    return 0;
}