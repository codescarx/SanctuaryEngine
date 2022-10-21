#ifndef HEIGHTMAP
#define HEIGHTMAP

#include <GL/glew.h>
#include "GlResource.h"

class Heightmap : public GlResource {
public:
    Heightmap(const char *filename, float amplitude);
    ~Heightmap();
    void bindHeightmap(unsigned unit);
    void bindNormalmap(unsigned unit);
    const float amplitude;
private:
    GLuint heightmapId, normalmapId;
};

#endif /* HEIGHTMAP */
