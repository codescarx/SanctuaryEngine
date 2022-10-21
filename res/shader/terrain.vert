#version 430 core

layout (location = 0) out vec2 outUv;

uniform vec3 pos;
uniform float tileSize;

const vec3 offset[4] = {
    vec3(0, 0, 0), vec3(1, 0, 0), vec3(1, 0, 1), vec3(0, 0, 1)
};
const vec2 uv[4] = {
    vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1)
};

void main(void) {
    gl_Position = vec4(pos + tileSize * offset[gl_VertexID], 1.0);
    outUv = uv[gl_VertexID];
}