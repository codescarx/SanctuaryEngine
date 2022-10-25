#version 430 core

layout (location = 0) out vec2 outUv;

const vec2 pos[4] = {
    vec2(-1, 1), vec2(-1, -1), vec2(1, 1), vec2(1, -1)
};

void main(void) {
    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    outUv = pos[gl_VertexID] * 0.5 + 0.5;
}