#version 430 core

layout (location = 0) in vec2 inUv;

layout (location = 0) out vec4 colour;
layout (location = 1) out vec4 normals;
layout (location = 2) out vec4 meta;

layout (binding = 0) uniform sampler2D tex;
layout (binding = 1) uniform sampler2D heightmap;
layout (binding = 2) uniform sampler2D normalmap;

uniform float textureTiling;

void main(void) {
    colour = vec4(texture(tex, inUv * textureTiling).rgb, 1.0);
    normals = vec4(texture(normalmap, inUv).rgb, 1.0);
    meta = vec4(1.0, 0.0, 0.0, 1.0);
}