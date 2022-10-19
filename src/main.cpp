#include "Engine.h"

int main(void) {
    
    Engine engine(1920, 1080, "Engine Demo");

    while (!engine.windowShouldClose()) {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        engine.update();
    }

    return 0;
}