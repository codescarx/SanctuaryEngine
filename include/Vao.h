#ifndef VAO
#define VAO

#include <GL/glew.h>

class Vao {
public:
    Vao();
    ~Vao();
    const GLuint vaoId;
};

#endif /* VAO */
