#include "Vao.h"

#include "util.h"

#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


Vao::Vao() : vaoId([](){ GLuint tmp; glGenVertexArrays(1, &tmp); return tmp; }()) {}

Vao::Vao(const std::vector<Vertex> &vertices) : vaoId([](){ GLuint tmp; glCreateVertexArrays(1, &tmp); return tmp; }()), numVertices(vertices.size()) {
    GLuint vbo;
    glCreateBuffers(1, &vbo);
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
    glVertexArrayAttribFormat(vaoId, 2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
}

Vao::~Vao() {
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(vbos.size(), vbos.data());
}

Vao* Vao::loadFromObj(const char *filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, nullptr);
    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }
    if (!err.empty()) {
        fatal(err.c_str());
    }

    const tinyobj::shape_t &shape = shapes[0];
    int i = 0;
    std::vector<Vertex> vertices;
    for (int f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
        for (int v = 0; v < 3; v++) {
            tinyobj::index_t idx = shape.mesh.indices[i++];

            glm::vec3 position = {
                attrib.vertices[3 * idx.vertex_index + 0],
                attrib.vertices[3 * idx.vertex_index + 1],
                attrib.vertices[3 * idx.vertex_index + 2]
            };
            glm::vec2 uv = {
                attrib.texcoords[2 * idx.texcoord_index + 0],
                attrib.texcoords[2 * idx.texcoord_index + 1]
            };
            glm::vec3 normal = {
                attrib.normals[3 * idx.normal_index + 0],
                attrib.normals[3 * idx.normal_index + 1],
                attrib.normals[3 * idx.normal_index + 2]
            };

            Vertex vertex{position, uv, normal};
            vertices.push_back(vertex);
        }
    }

    return new Vao(vertices);
}