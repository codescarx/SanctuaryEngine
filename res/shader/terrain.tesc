#version 430 core

layout (vertices = 4) out;

layout (location = 0) in vec2 inUv[];

layout (location = 0) out vec2 outUv[4];

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec2 screenDim;
uniform float tessDivisor;

float tessFactor(vec4 p0, vec4 p1) {
    vec4 mid = (p0 + p1) * 0.5;
    float radius = distance(p0, p1) * 0.5;

    vec4 v = viewMatrix * mid;
    vec4 clip0 = (projectionMatrix * (v - vec4(radius, 0.f, 0.f, 0.f)));
    vec4 clip1 = (projectionMatrix * (v + vec4(radius, 0.f, 0.f, 0.f)));
    clip0 /= clip0.w; clip1 /= clip1.w;
    clip0.xy *= screenDim; clip1.xy *= screenDim;

    return clamp(distance(clip0, clip1) / tessDivisor, 1.0, 64.0);
}

void main(void) {
    if (gl_InvocationID == 0) {
        gl_TessLevelOuter[0] = tessFactor(gl_in[3].gl_Position, gl_in[0].gl_Position);
        gl_TessLevelOuter[1] = tessFactor(gl_in[0].gl_Position, gl_in[1].gl_Position);
        gl_TessLevelOuter[2] = tessFactor(gl_in[1].gl_Position, gl_in[2].gl_Position);
        gl_TessLevelOuter[3] = tessFactor(gl_in[2].gl_Position, gl_in[3].gl_Position);
        gl_TessLevelInner[0] = mix(gl_TessLevelOuter[0], gl_TessLevelOuter[3], 0.5);
        gl_TessLevelInner[1] = mix(gl_TessLevelOuter[2], gl_TessLevelOuter[1], 0.5);
    }
    
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    outUv[gl_InvocationID] = inUv[gl_InvocationID];
}