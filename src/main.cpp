#include "Engine.h"

#include <iostream>

int main(void) {
    
    Engine engine(1920, 1080, "Engine Demo");

    while (!engine.windowShouldClose()) {

        if (engine.getDisplay()->isKeyDown(GLFW_KEY_W)) glClearColor(1, 0, 0, 1);
        else glClearColor(1, 1, 0, 1);

        std::cout << engine.getDelta() << std::endl;

        glClear(GL_COLOR_BUFFER_BIT);
        engine.update();
    }

    return 0;
}