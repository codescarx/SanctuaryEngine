#include "Fbo.h"

#include "Engine.h"

Fbo::Fbo(int width, int height, const std::vector<GLenum> colourAttachments, bool depthAttachment) : width(width), height(height), colourAttachments(colourAttachments), depthAttachment(depthAttachment) {
    setup();
}

void Fbo::bindToDraw() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);
    glViewport(0, 0, width, height);
}
void Fbo::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Engine::instance->getDisplay()->getWidth(), Engine::instance->getDisplay()->getHeight());
}

void Fbo::resize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    cleanup();
    setup();
}

void Fbo::setup() {
    glGenFramebuffers(1, &fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    std::vector<GLenum> drawBuffers;
    for (unsigned i = 0; i < colourAttachments.size(); i++)
        drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    glDrawBuffers(drawBuffers.size(), drawBuffers.data());

    for (unsigned i = 0; i < colourAttachments.size(); i++) {
        GLenum format = colourAttachments[i];

        GLuint textureId;
        glGenTextures(1, &textureId);
        textureIds.push_back(textureId);

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureId, 0);
    }

    if (depthAttachment) {
        GLuint textureId;
        glGenTextures(1, &textureId);
        textureIds.push_back(textureId);

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);
    }

    unbind();
}

void Fbo::cleanup() {
    glDeleteFramebuffers(1, &fboId);
    glDeleteTextures(textureIds.size(), textureIds.data());
    textureIds.clear();
}

Fbo::~Fbo() {
    cleanup();
}