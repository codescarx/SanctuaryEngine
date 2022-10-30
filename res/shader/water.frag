#version 430 core

layout (location = 0) in vec2 inUv;

layout (location = 0) out vec4 colour;
layout (location = 1) out vec4 normals;
layout (location = 2) out vec4 meta;

layout (binding = 0) uniform sampler2D heightmap;
layout (binding = 1) uniform sampler2D normalmap;

uniform float tiling;

void main(void) {
    colour = vec4(0.349, 0.384, 0.563, 1.0);
    normals = vec4(texture(normalmap, inUv * tiling).rgb, 1.0);
    meta = vec4(1.0, 2.0, 400.0, 1.0);   
}