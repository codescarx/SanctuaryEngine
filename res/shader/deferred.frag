#version 430 core

layout (location = 0) in vec2 uv;

layout (binding = 0) uniform sampler2D depthTexture;

layout (binding = 1) uniform sampler2D colourTexture;
layout (binding = 2) uniform sampler2D normalTexture;
layout (binding = 3) uniform sampler2D metaTexture;

layout (location = 0) out vec4 outColour;

void main(void) {
    outColour = texture(colourTexture, uv);
    //outColour = vec4(1.0, 0.0, 0.0, 1.0);
}