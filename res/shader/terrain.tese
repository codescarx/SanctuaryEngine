#version 430 core

layout (quads, fractional_even_spacing, cw) in;

layout (location = 0) in vec2 inUv[];

layout (location = 0) out vec2 outUv;

uniform mat4 vpMatrix;
uniform float amplitude;
layout (binding = 1) uniform sampler2D heightmap;

void main(void) {
    vec4 pos1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
	vec4 pos2 = mix(gl_in[3].gl_Position, gl_in[2].gl_Position, gl_TessCoord.x);
	vec4 pos = mix(pos1, pos2, gl_TessCoord.y);

    vec2 uv1 = mix(inUv[0], inUv[1], gl_TessCoord.x);
	vec2 uv2 = mix(inUv[3], inUv[2], gl_TessCoord.x);
	outUv = mix(uv1, uv2, gl_TessCoord.y);

    pos.y += 2.0 * (texture(heightmap, outUv).r - 0.5) * amplitude;

    gl_Position = vpMatrix * pos;
}