#include "Heightmap.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
#include <stb/stb_image.h>
#include "NormalCompute.h"

Heightmap::Heightmap(const char *filename, float amplitude, float normalStrength) : amplitude(amplitude), normalStrength(normalStrength) {
    glGenTextures(1, &heightmapId);
    glGenTextures(1, &normalmapId);

    int width, height, channels;
    unsigned short *data = stbi_load_16(filename, &width, &height, &channels, 1);
    assert(channels == 1);
    
    glBindTexture(GL_TEXTURE_2D, heightmapId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_SHORT, data);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, normalmapId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    NormalCompute comp;
    comp.compute(width, heightmapId, normalStrength, normalmapId);
}

void Heightmap::bindHeightmap(unsigned unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, heightmapId);
}
void Heightmap::bindNormalmap(unsigned unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, normalmapId);
}

Heightmap::~Heightmap() {
    glDeleteTextures(1, &heightmapId);
    glDeleteTextures(1, &normalmapId);
}