#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

static GLuint genTextureId() {
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

Texture::Texture(int width, int height, float *data): textureId(genTextureId()), target(GL_TEXTURE_2D) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, data);
}

Texture::Texture(const char *filename, bool heightmap) : textureId(genTextureId()), target(GL_TEXTURE_2D) {
    if (heightmap) {
        loadHeightmap(filename);
        return;
    }
    
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 4);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::loadHeightmap(const char *filename) {
    int width, height, channels;
    unsigned short *data = stbi_load_16(filename, &width, &height, &channels, 1);
    assert(channels == 1);
    
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_SHORT, data);

    stbi_image_free(data);
}

// +x -x +y -y +z -z
Texture::Texture(const std::vector<const char *> &filenames) : textureId(genTextureId()), target(GL_TEXTURE_CUBE_MAP) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    for (unsigned i = 0; i < 6; i++) {
        int width, height, channels;
        unsigned char *data = stbi_load(filenames[i], &width, &height, &channels, 4);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 
}

void Texture::bind(unsigned unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, textureId);
}

void Texture::bindImage(unsigned unit, GLenum access) {
    glBindImageTexture(unit, textureId, 0, GL_FALSE, 0, access, GL_RGBA32F);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}