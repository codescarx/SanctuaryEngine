#include "Vao.h"

Vao::Vao() : vaoId([](){ GLuint tmp; glGenVertexArrays(1, &tmp); return tmp; }()) {}

Vao::Vao(const std::vector<Vertex> &vertices) : vaoId([](){ GLuint tmp; glGenVertexArrays(1, &tmp); return tmp; }()) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    vbos.push_back(vbo);

    glNamedBufferStorage(vbo, vertices.size() * sizeof(Vertex), vertices.data(), 0);

    glVertexArrayVertexBuffer(vaoId, 0, vbo, 0, sizeof(Vertex));
    
    for (int i = 0; i < 3; i++) {
        glEnableVertexArrayAttrib(vaoId, i);
        glVertexArrayAttribBinding(vaoId, i, 0);
        glVertexArrayBindingDivisor(vaoId, i, 0); // if the divisor is non-zero it becomes an instanced attribute?
    }

    glVertexArrayAttribFormat(vaoId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexArrayAttribFormat(vaoId, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
    glVertexArrayAttribFormat(vaoId, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
}

Vao::~Vao() {
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(vbos.size(), vbos.data());
}