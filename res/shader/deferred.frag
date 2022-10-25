#version 430 core

layout (location = 0) in vec2 uv;

layout (binding = 0) uniform sampler2D depthTexture;

layout (binding = 1) uniform sampler2D colourTexture;
layout (binding = 2) uniform sampler2D normalTexture;
layout (binding = 3) uniform sampler2D metaTexture;

layout (binding = 4) uniform samplerCube skyboxTexture;

layout (location = 0) out vec4 deferredOutput;

uniform mat4 invViewMatrix;
uniform mat4 invProjectionMatrix;
uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 cameraPos;
uniform float ambientLight;
uniform float fogDensity;
uniform float fogGradient;

vec3 getWorldPos() {
    float z = texture(depthTexture, uv).r * 2.0 - 1.0;

    vec4 clipSpace = vec4(uv * 2.0 - 1.0, z, 1.0);
    vec4 viewSpace = invProjectionMatrix * clipSpace;
    viewSpace /= viewSpace.w;

    vec4 worldSpace = invViewMatrix * viewSpace;
    return worldSpace.xyz;
}

void main(void) {
    vec3 fragPos = getWorldPos();
    vec3 colour = texture(colourTexture, uv).rgb;
    vec3 normal = texture(normalTexture, uv).xyz;
    vec4 meta = texture(metaTexture, uv);
    vec3 skyColour = texture(skyboxTexture, fragPos - cameraPos).rgb;

    if (meta.r < 0.5) {
        deferredOutput = vec4(skyColour, 1.0);
        return;
    }

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 result = max(dot(normal, lightDirection), ambientLight) * colour * lightColour;

    float dist = length(cameraPos - fragPos);
    float visibility = exp(-pow(dist * fogDensity, fogGradient));
    visibility = clamp(visibility, 0.0, 1.0);
    result = mix(skyColour, result, visibility);

    deferredOutput = vec4(result, 1.0);
}