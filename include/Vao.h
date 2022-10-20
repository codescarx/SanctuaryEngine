#ifndef VAO
#define VAO

#include <GL/glew.h>
#include "GlResource.h"

class Vao : public GlResource {
public:
    Vao();
    ~Vao();
    const GLuint vaoId;
    
    inline void bind() { glBindVertexArray(vaoId); }
    inline void unbind() { glBindVertexArray(0); }
};

#endif /* VAO */
