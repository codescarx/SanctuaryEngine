#ifndef FBO
#define FBO

#include <GL/glew.h>
#include <vector>
#include "GlResource.h"

class Fbo : public GlResource {
public:
    Fbo(int width, int height, const std::vector<GLenum> colourAttachments, bool depthAttachment);
    ~Fbo();
    void resize(int newWidth, int newHeight);
    void bindToWrite();
    //void bindToRead(unsigned u);
    void unbind();
private:
    int width, height;
    GLuint fboId;
    const std::vector<GLenum> colourAttachments;
    const bool depthAttachment;
    std::vector<GLuint> textureIds;
    void setup();
    void cleanup();
};

#endif /* FBO */
