#version 430 core

layout (location = 0) in vec2 inUv;

layout (location = 0) out vec4 colour;

layout (location = 0) uniform sampler2D tex;

uniform float textureTiling;

void main(void) {
    colour = vec4(texture(tex, inUv * textureTiling).rgb, 1.0);
}