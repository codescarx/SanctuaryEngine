#version 430 core

layout (location = 0) in vec2 uv;
layout (location = 1) in vec3 normal;

layout (location = 0) out vec4 colour;
layout (location = 1) out vec4 normals;
layout (location = 2) out vec4 meta;

layout (binding = 0) uniform sampler2D tex;

void main(void) {
    colour = vec4(texture(tex, uv).rgb, 1.0);
    normals = normal;
    meta = vec4(1.0, 0.0, 1.0, 1.0);
}