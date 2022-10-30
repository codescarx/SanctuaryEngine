#version 430 core

layout (location = 0) out vec2 outUv;

uniform vec3 position;
uniform float tileSize;
uniform int tileCnt;

const vec2 uv[4] = {
    vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1)
};

void main(void) {
    int i = gl_InstanceID / tileCnt, j = gl_InstanceID % tileCnt;

    vec2 pos = position.xz + tileSize * (vec2(i, j) + uv[gl_VertexID]);
    gl_Position = vec4(pos.x, position.y, pos.y, 1.0);

    outUv = (1.0 / tileCnt) * (vec2(i, j) + uv[gl_VertexID]);
}