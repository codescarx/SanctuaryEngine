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

const int iter = 15;
uniform float waterLevel;
uniform float A;
uniform float tiling;
uniform vec3 waterColour;
float sunScale = 3.0;
float fadeSpeed = 0.15;
vec3 depthColour = vec3(0.0039, 0.00196, 0.145) * 1.5;
vec3 extinction = vec3(7.0, 30.0, 40.0);
float waterVisibility = 4.0;
float shoreHardness = 1.0;

vec3 light(vec3 colour, vec3 pos, vec3 normal, float reflectivity, float shineDamper) {
    vec3 toLightVector = -lightDirection;

    vec3 diffuse = max(dot(normal, toLightVector), ambientLight) * lightColour * colour;

    float specularFactor = max(dot(reflect(lightDirection, normal), normalize(cameraPos - pos)), 0.0);
    specularFactor = pow(specularFactor, shineDamper);
    vec3 specular = specularFactor * reflectivity * lightColour;

    return diffuse + specular;
}

vec3 fog(vec3 colour, vec3 fogColour, vec3 pos) {
    float dist = length(cameraPos - pos);
    float visibility = exp(-pow(dist * fogDensity, fogGradient));
    visibility = clamp(visibility, 0.0, 1.0);
    return mix(fogColour, colour, visibility);
}

float fresnelTerm(vec3 normal, vec3 viewDir) {
    const float R0 = 0.5;
    float angle = 1.0 - clamp(dot(normal, viewDir), 0.0, 1.0);
    float fresnel = angle * angle;
    fresnel = fresnel * fresnel;
    fresnel = fresnel * angle;
    return clamp(fresnel * (1.0 - clamp(R0, 0.0, 1.0)) + R0, 0.0, 1.0);
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
    
    vec3 reflection = waterColour;
    vec3 refraction = originalColour;

    float fresnel = fresnelTerm(normal, viewDir);
    
    float depthN = depth * fadeSpeed;
    float thing = clamp(length(lightColour) / sunScale, 0.0, 1.0);
    refraction = mix(mix(refraction, thing * waterColour, clamp(depthN / waterVisibility, 0.0, 1.0)),
						  thing * depthColour, clamp(vdepth / extinction, 0.0, 1.0));

    vec3 result = mix(refraction, reflection, fresnel);
    result = light(result, surfacePoint, normal, 0.8, 120.0);
    result = mix(refraction, result, clamp(depth * shoreHardness, 0.0, 1.0));
    
    if (position.y > level) {
        result = originalColour;
        surfacePoint = position;
    }
    return fog(result, texture(skyboxTexture, surfacePoint - cameraPos).rgb, surfacePoint);
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

    vec3 result = light(colour, fragPos, normal, meta.g, meta.b);
    result = fog(result, skyColour, fragPos);

    deferredOutput = vec4(result, 1.0);
}