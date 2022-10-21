#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

static GLuint genTextureId() {
    GLuint id;
    glGenTextures(1, &id);
    return id;
}

Texture::Texture(const char *filename) : textureId(genTextureId()), target(GL_TEXTURE_2D) {
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

void Texture::bind(unsigned unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, textureId);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}