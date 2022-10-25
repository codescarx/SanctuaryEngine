#include "Deferred.h"

void Deferred::doDeferredShading(Scene *scene, Fbo *deferredFbo) {
    shader.use();
    dummyVao->bind();

    shader.loadSceneData(scene);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, deferredFbo->getDepthAttachmentTextureId());
    for (unsigned i = 0; i < 3; i++) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, deferredFbo->getColourAttachmentTextureId(i));
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shader.disuse();
    dummyVao->unbind();
}