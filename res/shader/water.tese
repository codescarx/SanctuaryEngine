#version 430 core

layout (quads, fractional_even_spacing, cw) in;

layout (location = 0) in vec2 inUv[];

layout (location = 0) out vec2 outUv;

uniform mat4 vpMatrix;
uniform float tiling;
uniform float heightScale;
uniform float choppiness;
layout (binding = 0) uniform sampler2D heightmap;
layout (binding = 1) uniform sampler2D dxMap;
layout (binding = 2) uniform sampler2D dzMap;

void main(void) {
    vec4 pos1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
	vec4 pos2 = mix(gl_in[3].gl_Position, gl_in[2].gl_Position, gl_TessCoord.x);
	vec4 pos = mix(pos1, pos2, gl_TessCoord.y);

    vec2 uv1 = mix(inUv[0], inUv[1], gl_TessCoord.x);
	vec2 uv2 = mix(inUv[3], inUv[2], gl_TessCoord.x);
	outUv = mix(uv1, uv2, gl_TessCoord.y);

    float dx = texture(dxMap, outUv * tiling).r * choppiness;
    float dy = texture(heightmap, outUv * tiling).r * heightScale;
    float dz = texture(dzMap, outUv * tiling).r * choppiness;
    pos += vec4(-dx, dy, -dz, 0.0);

    gl_Position = vpMatrix * pos;
}