#ifndef TEXTURE
#define TEXTURE

#include "GlResource.h"

#include <GL/glew.h>

class Texture : public GlResource {
public:
    Texture(const char *filename);
    ~Texture();
    void bind(unsigned unit);
private:
    const GLuint textureId;
    const GLenum target;
};

#endif /* TEXTURE */
