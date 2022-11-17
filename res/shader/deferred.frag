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

layout (binding = 5) uniform sampler2D waterNormalTexture;
layout (binding = 6) uniform sampler2D waterDepthTexture;

uniform float waterReflectivity;
uniform float waterShineDamper;
uniform float fadeSpeed;

const int iter = 15;
uniform float waterLevel;
uniform float A;
uniform float tiling;
uniform vec3 waterColour;
float sunScale = 3.0;
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

// vec3 water(vec3 position, vec3 originalColour) {
//     vec3 viewDir = normalize(position - cameraPos);

//     float level = waterLevel;
//     float t = (level - cameraPos.y) / viewDir.y;
//     vec3 surfacePoint = cameraPos + viewDir * t;

//     vec2 uv;
//     float recip = 1.0 / iter;
//     for (int i = 0; i < iter; i++) {
//         uv = (surfacePoint.xz + viewDir.xz * recip) * tiling;
//         float bias = texture(waterHeightmap, uv).r * recip;
//         level += bias;
//         t = (level - cameraPos.y) / viewDir.y;
//         surfacePoint = cameraPos + viewDir * t;
//     }

//     float depth = length(position - surfacePoint);
//     float vdepth = surfacePoint.y - position.y;

//     viewDir = normalize(cameraPos - surfacePoint);

//     vec3 normal = texture(waterNormalmap, uv).rgb;
    
//     vec3 reflection = waterColour;
//     vec3 refraction = originalColour;

//     float fresnel = fresnelTerm(normal, viewDir);
    
//     float depthN = depth * fadeSpeed;
//     float thing = clamp(length(lightColour) / sunScale, 0.0, 1.0);
//     refraction = mix(mix(refraction, thing * waterColour, clamp(depthN / waterVisibility, 0.0, 1.0)),
// 						  thing * depthColour, clamp(vdepth / extinction, 0.0, 1.0));

//     vec3 result = mix(refraction, reflection, fresnel);
//     result = light(result, surfacePoint, normal, 0.8, 120.0);
//     result = mix(refraction, result, clamp(depth * shoreHardness, 0.0, 1.0));
    
//     if (position.y > level) {
//         result = originalColour;
//         surfacePoint = position;
//     }
//     return fog(result, texture(skyboxTexture, surfacePoint - cameraPos).rgb, surfacePoint);
// }

vec3 getWorldPos() {
    float z = texture(depthTexture, uv).r * 2.0 - 1.0;

    vec4 clipSpace = vec4(uv * 2.0 - 1.0, z, 1.0);
    vec4 viewSpace = invProjectionMatrix * clipSpace;
    viewSpace /= viewSpace.w;

    vec4 worldSpace = invViewMatrix * viewSpace;
    return worldSpace.xyz;
}

vec3 getWaterPos() {
    float z = texture(waterDepthTexture, uv).r * 2.0 - 1.0;

    vec4 clipSpace = vec4(uv * 2.0 - 1.0, z, 1.0);
    vec4 viewSpace = invProjectionMatrix * clipSpace;
    viewSpace /= viewSpace.w;

    vec4 worldSpace = invViewMatrix * viewSpace;
    return worldSpace.xyz;
}

// vec3 getWaterColour(float dist, vec3 sam) {
//     const vec3 K = vec3(0.46, 0.09, 0.06);
//     const float b = 0.11;
//     const vec3 scatter = vec3(0.349, 0.384, 0.493) * 0.65;//vec3(0.05, 0.05, 0.10);

//     vec3 refraction = sam * exp(-K * dist);
//     float bactual = 1.0 - exp(-b * dist);
//     return mix(refraction, scatter, bactual) * lightColour;
// }

float fresnelTerm(vec3 normal, vec3 viewDir) {
    const float R0 = 0.5;
    float angle = 1.0 - clamp(dot(normal, viewDir), 0.0, 1.0);
    float fresnel = angle * angle;
    fresnel = fresnel * fresnel;
    fresnel = fresnel * angle;
    return clamp(fresnel * (1.0 - clamp(R0, 0.0, 1.0)) + R0, 0.0, 1.0);
}

float fresnelSchlick(vec3 position, vec3 normal) {
    float cosTheta = dot(normal, normalize(cameraPos - position));
	float F0 = 0.02;
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float saturate(float x) {
    return clamp(x, 0.0, 1.0);
}

vec3 getWaterColour(vec3 originalColour, vec3 position, vec3 normal, float depth, float vdepth) {

    const float diffuseStrength = 1.5;
    const vec3 diffuseColour = diffuseStrength * vec3(0.064, 0.085, 0.12);

    float ambientStrength = 0.5;
    vec3 ambientColour = 0.5 * diffuseColour;
    vec3 scatterColour = vec3(0.05, 0.8, 0.7);
    float specularStrength = 1.0;
    float scatterStrength = 0.5;
    float distortion = 0.2;

    float power = 8.0;
    float scale = 0.4;

    vec3 lightDir = -lightDirection;

    ///////////////////////////////

    vec3 result = vec3(0.0);

    vec3 rayDir = normalize(position - cameraPos);
    vec3 halfwayDir = normalize(lightDir - rayDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 512.0);

    vec3 specular = spec * lightColour;

    float sun = max(dot(normal, lightDir), 0.0);
    vec3 sunlight = sun * lightColour;

    float sky = max(dot(normal, vec3(0.0, 1.0, 0.0)), 0.0);
    vec3 skylight = sky * vec3(0.09, 0.43, 0.51);

    result += sunlight;
    result += skylight;

    float A = 1.5;
    float heightFraction = saturate((position.y + A) / (2.0 * A));

    vec3 col = mix(ambientColour, 0.5 * scatterColour, pow(0.5 + 0.5 * rayDir.y, 2.0));

    result *= diffuseColour;
    result += ambientStrength * col + specularStrength * specular;

    vec3 h = normalize(-lightDir + normal * distortion);
    float vDotH = pow(saturate(dot(rayDir, -h)), power) * scale;

    float dist = length(cameraPos - position);
    result += scatterStrength * pow((1.0-position.y/A), 4.0) * 
                heightFraction * vDotH * scatterColour;
    
    vec3 reflectedDir = normalize(reflect(rayDir, normal));
    reflectedDir.y = max(0.1, reflectedDir.y);
    vec3 reflectedCol = texture(skyboxTexture, reflectedDir).rgb;
    float fresnel = saturate(fresnelSchlick(position, normal));
    result = mix(result, 0.5 * reflectedCol, fresnel);

    return result;

    // const vec3 waterColour = vec3(0.349, 0.384, 0.493) * 0.65;
    // const vec3 depthColour = waterColour * 0.8;
    // const float shoreHardness = 0.5;

    // vec3 reflection = waterColour * 1.5;
    // vec3 refraction = originalColour;

    // vec3 viewDir = normalize(cameraPos - position);
    // float fresnel = fresnelTerm(normal, viewDir);
    
    // float depthN = depth * fadeSpeed;
    // float thing = clamp(length(lightColour) / sunScale, 0.0, 1.0);
    // refraction = mix(mix(refraction, thing * waterColour, clamp(depthN / waterVisibility, 0.0, 1.0)),
	// 					  thing * depthColour, clamp(vdepth / extinction, 0.0, 1.0));

    // vec3 result = mix(refraction, reflection, fresnel);
    // result = light(result, position, normal, waterReflectivity, waterShineDamper);
    // result = mix(refraction, result, clamp(depth * shoreHardness, 0.0, 1.0));

    // return result;
}


void main(void) {
    vec3 fragPos = getWorldPos();
    vec3 waterPos = getWaterPos();
    vec3 colour = texture(colourTexture, uv).rgb;
    vec3 normal = texture(normalTexture, uv).xyz;
    vec4 meta = texture(metaTexture, uv);
    vec3 skyColour = texture(skyboxTexture, fragPos - cameraPos).rgb;

    vec3 result = light(colour, fragPos, normal, meta.g, meta.b);

    if (meta.r < 0.5) {
        result = skyColour;
    }

    if (length(waterPos - cameraPos) < length(fragPos - cameraPos)) {
        result = getWaterColour(result, waterPos, texture(waterNormalTexture, uv).xyz, length(fragPos - waterPos), waterPos.y - fragPos.y);
        fragPos = waterPos;
    }

    result = fog(result, skyColour, fragPos);

    deferredOutput = vec4(result, 1.0);
}