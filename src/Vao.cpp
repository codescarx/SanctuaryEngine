#include "Vao.h"

Vao::Vao() : vaoId([](){ GLuint tmp; glGenVertexArrays(1, &tmp); return tmp; }()) {

}

Vao::~Vao() {
    glDeleteVertexArrays(1, &vaoId);
}