#ifndef TEXTURE
#define TEXTURE

#include "GlResource.h"

#include <GL/glew.h>

class Texture : public GlResource {
public:
    Texture(const char *filename);
    ~Texture();
private:
    const GLuint textureId;
    inline GLuint genTextureId() {
        GLuint id;
        glGenTextures(1, &id);
        return id;
    }
};

#endif /* TEXTURE */
