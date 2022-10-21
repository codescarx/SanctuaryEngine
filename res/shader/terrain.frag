#version 430 core

layout (location = 0) in vec2 inUv;

layout (location = 0) out vec4 colour;

layout (binding = 0) uniform sampler2D tex;
layout (binding = 1) uniform sampler2D heightmap;
layout (binding = 2) uniform sampler2D normalmap;

uniform float textureTiling;

void main(void) {
    colour = vec4(texture(tex, inUv * textureTiling).rgb, 1.0);
}