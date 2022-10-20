#ifndef VAO
#define VAO

#include <GL/glew.h>
#include "GlResource.h"

class Vao : public GlResource {
public:
    Vao();
    ~Vao();
    const GLuint vaoId;
};

#endif /* VAO */
