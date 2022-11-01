#ifndef VAO
#define VAO

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "GlResource.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
};

class Vao : public GlResource {
public:
    Vao();
    Vao(const std::vector<Vertex> &vertices);
    ~Vao();
    const GLuint vaoId;
    
    inline void bind() { glBindVertexArray(vaoId); }
    inline void unbind() { glBindVertexArray(0); }
private:
    std::vector<GLuint> vbos;
};

#endif /* VAO */
