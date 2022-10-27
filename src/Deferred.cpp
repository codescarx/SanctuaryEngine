#include "Deferred.h"

void Deferred::doDeferredShading(Scene *scene, Camera *camera, Fbo *deferredFbo) {
    shader.use();
    dummyVao->bind();

    shader.loadData(scene, camera);

    glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, deferredFbo->getDepthAttachmentTextureId());
    scene->water->getHktTexture()->bind(0);
    for (unsigned i = 0; i < 3; i++) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, deferredFbo->getColourAttachmentTextureId(i));
    }
    scene->skyboxTexture->bind(4);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shader.disuse();
    dummyVao->unbind();
}