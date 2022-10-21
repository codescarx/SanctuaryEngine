#include "Heightmap.h"

#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include "stb/stb_image.h"

static float get(unsigned short *data, int width, int height, int x, int z) {
    x = std::clamp(x, 0, width - 1);
    z = std::clamp(z, 0, height - 1);
    return float(data[width * z + x]) / 65535.f;
}

Heightmap::Heightmap(const char *filename, float amplitude) : amplitude(amplitude) {
    glGenTextures(1, &heightmapId);
    glGenTextures(1, &normalmapId);

    int width, height, channels;
    unsigned short *data = stbi_load_16(filename, &width, &height, &channels, 1);
    
    glBindTexture(GL_TEXTURE_2D, heightmapId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_SHORT, data);

    float *normals = new float[width * height * 3];

    for (int x = 0; x < width; x++) {
        for (int z = 0; z < height; z++) {
            float tl = get(data, width, height, x-1, z-1); // top left
            float l = get(data, width, height, x-1, z);   // left
            float bl = get(data, width, height, x-1, z+1); // bottom left
            float t = get(data, width, height, x, z-1);   // top
            float b = get(data, width, height, x, z+1);   // bottom
            float tr = get(data, width, height, x+1, z-1); // top right
            float r = get(data, width, height, x+1, z);   // right
            float br = get(data, width, height, x+1, z+1); // bottom right

            float dx = (tr + 2.f * r + br) - (tl + 2.f * l + bl);
            float dz = (bl + 2.f * b + br) - (tl + 2.f * t + tr);
            float dy = 1.f / amplitude;

            glm::vec3 normal = glm::normalize(glm::vec3(dx, dy, dz));
            normals[width * z + x + 0] = normal.x;
            normals[width * z + x + 1] = normal.y;
            normals[width * z + x + 2] = normal.z;
        }
    }

    glBindTexture(GL_TEXTURE_2D, normalmapId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, data);

    stbi_image_free(data);
    delete[] normals;
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