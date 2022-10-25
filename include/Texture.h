#ifndef TEXTURE
#define TEXTURE

#include "GlResource.h"

#include <GL/glew.h>
#include <vector>

class Texture : public GlResource {
public:
    Texture(const char *filename);
    Texture(const std::vector<const char *> &filenames); // +x -x +y -y +z -z
    ~Texture();
    void bind(unsigned unit);
private:
    const GLuint textureId;
    const GLenum target;
};

#endif /* TEXTURE */
