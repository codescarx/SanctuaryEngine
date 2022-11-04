#include "NormalCompute.h"

NormalCompute::NormalCompute() : Shader("res/shader/normal.comp", {"N", "strength"}) {}

void NormalCompute::compute(int N, Texture *heightTex, float strength, Texture *normalTex) {
    use();

    heightTex->bind(0);
    normalTex->bindImage(0, GL_WRITE_ONLY);
    loadFloat("N", N);
    loadFloat("strength", strength);

    dispatchCompute(N, N, 1);

    disuse();
}

void NormalCompute::compute(int N, GLuint heightTex, float strength, GLuint normalTex) {
    use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightTex);
    glBindImageTexture(0, normalTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    loadFloat("N", N);
    loadFloat("strength", strength);

    dispatchCompute(N, N, 1);

    disuse();
}