#version 430 core

uniform vec3 pos;
uniform float tileSize;
uniform mat4 vpMatrix;

const vec3 offset[4] = {
    vec3(0,0,0), vec3(1,0,0), vec3(1,0,1), vec3(0,0,1)
};

void main(void) {
    gl_Position = vec4(pos + 50.0 * offset[gl_VertexID], 1.0);
}