#version 430 core

layout (location = 0) in vec2 inUv;

layout (location = 0) out vec4 normals;

layout (binding = 3) uniform sampler2D normalmap;

uniform float tiling;

void main(void) {
    normals = vec4(texture(normalmap, inUv * tiling).rgb, 1.0);
}