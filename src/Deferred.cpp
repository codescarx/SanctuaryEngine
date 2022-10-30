#include "Deferred.h"

void Deferred::doDeferredShading(Scene *scene, Camera *camera, Fbo *gBuffer, Fbo *waterFbo) {
    shader.use();
    dummyVao->bind();

    shader.loadData(scene, camera);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gBuffer->getDepthAttachmentTextureId());
    for (unsigned i = 0; i < 3; i++) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, gBuffer->getColourAttachmentTextureId(i));
    }
    scene->skyboxTexture->bind(4);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, waterFbo->getColourAttachmentTextureId(0));
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, waterFbo->getDepthAttachmentTextureId());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shader.disuse();
    dummyVao->unbind();
}