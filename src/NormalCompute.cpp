#include "NormalCompute.h"

NormalCompute::NormalCompute() : Shader("res/shader/normal.comp", {"N", "amplitude"}) {}

void NormalCompute::compute(int N, Texture *heightTex, float amplitude, Texture *normalTex) {
    use();

    heightTex->bind(0);
    normalTex->bindImage(0, GL_WRITE_ONLY);
    loadFloat("N", N);
    loadFloat("amplitude", amplitude);

    glDispatchCompute(N, N, 1);

    disuse();
}

void NormalCompute::compute(int N, GLuint heightTex, float amplitude, GLuint normalTex) {
    use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightTex);
    glBindImageTexture(0, normalTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    loadFloat("N", N);
    loadFloat("amplitude", amplitude);

    glDispatchCompute(N, N, 1);

    disuse();
}