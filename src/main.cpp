#include "Engine.h"

int main(void) {
    
    Engine engine(1920, 1080, "Engine Demo");

    while (!engine.windowShouldClose()) {

        if (engine.getDisplay().isKeyDown(GLFW_KEY_W)) glClearColor(1, 0, 0, 1);
        else glClearColor(1, 1, 0, 1);
        
        glClear(GL_COLOR_BUFFER_BIT);
        engine.update();
    }

    return 0;
}