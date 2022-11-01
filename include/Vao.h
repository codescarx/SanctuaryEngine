#ifndef VAO
#define VAO

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <string.h>
#include "GlResource.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    bool operator<(const Vertex &that) const {
        return memcmp(this, &that, sizeof(Vertex)) < 0;
    }
};

class Vao : public GlResource {
public:
    Vao();
    Vao(const std::vector<Vertex> &vertices);
    ~Vao();
    const GLuint vaoId;
    
    inline void bind() { glBindVertexArray(vaoId); }
    inline void unbind() { glBindVertexArray(0); }

    static Vao* loadFromObj(const char *filename);
private:
    std::vector<GLuint> vbos;
};

#endif /* VAO */
