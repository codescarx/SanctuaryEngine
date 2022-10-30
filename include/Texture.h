#ifndef TEXTURE
#define TEXTURE

#include "GlResource.h"

#include <GL/glew.h>
#include <vector>

class Texture : public GlResource {
public:
    Texture(int width, int height, float *data, GLint filter = GL_LINEAR);
    Texture(const char *filename, bool heightmap = false);
    Texture(const std::vector<const char *> &filenames); // +x -x +y -y +z -z
    ~Texture();
    void bind(unsigned unit);
    void bindImage(unsigned unit, GLenum access);
    const GLuint textureId;
private:
    const GLenum target;
    void loadHeightmap(const char *filename);
};

#endif /* TEXTURE */
