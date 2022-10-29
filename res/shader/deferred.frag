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

// water

layout (binding = 5) uniform sampler2D waterHeightmap;
layout (binding = 6) uniform sampler2D waterNormalmap;

const int iter = 10;
uniform float waterLevel;
uniform float A;
uniform float tiling;
uniform vec3 waterColour;

vec3 light(vec3 colour, vec3 pos, vec3 normal, float reflectivity, float shineDamper) {
    vec3 toLightVector = -lightDirection;

    vec3 diffuse = max(dot(normal, toLightVector), ambientLight) * lightColour * colour;

    float specularFactor = max(dot(reflect(lightDirection, normal), normalize(cameraPos - pos)), 0.0);
    specularFactor = pow(specularFactor, shineDamper);
    vec3 specular = specularFactor * reflectivity * lightColour;

    return diffuse + specular;
}

vec3 water(vec3 position, vec3 originalColour) {
    vec3 viewDir = normalize(position - cameraPos);

    float level = waterLevel;
    float t = (level - cameraPos.y) / viewDir.y;
    vec3 surfacePoint = cameraPos + viewDir * t;

    vec2 uv;
    float recip = 1.0 / iter;
    for (int i = 0; i < iter; i++) {
        uv = (surfacePoint.xz + viewDir.xz * recip) * tiling;
        float bias = texture(waterHeightmap, uv).r * recip;
        level += bias;
        t = (level - cameraPos.y) / viewDir.y;
        surfacePoint = cameraPos + viewDir * t;
    }

    float depth = length(position - surfacePoint);
    float vdepth = surfacePoint.y - position.y;

    viewDir = normalize(cameraPos - surfacePoint);

    vec3 normal = texture(waterNormalmap, uv).rgb;

    if (position.y > level) return originalColour;
    return light(waterColour, surfacePoint, normal, 0.8, 70.0);
}

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

    vec3 result = light(colour, fragPos, normal, 0.0, 0.0);

    float dist = length(cameraPos - fragPos);
    float visibility = exp(-pow(dist * fogDensity, fogGradient));
    visibility = clamp(visibility, 0.0, 1.0);
    result = mix(skyColour, result, visibility);

    if (fragPos.y <= waterLevel + A) {
        result = water(fragPos, result);
    }

    deferredOutput = vec4(result, 1.0);
}