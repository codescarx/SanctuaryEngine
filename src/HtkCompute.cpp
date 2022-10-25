#include "HktCompute.h"

#include "Engine.h"

HktCompute::HktCompute(int N, float length, Texture *h0Texture)
    : N(N), h0Texture(h0Texture), hktTexture(new Texture(N, N, nullptr)),
    Shader("res/shader/hkt.comp", {"N", "L", "t"})
{
    use();
    loadInt("N", N);
    loadFloat("L", length);
    disuse();
}

Texture* HktCompute::compute() {
    use();
    t += Engine::instance->getDelta() * 0.001f;
    loadFloat("t", t);

    h0Texture->bindImage(0, GL_READ_ONLY);
    hktTexture->bindImage(1, GL_WRITE_ONLY);

    glDispatchCompute(N/16, N/16, 1);
    disuse();

    return hktTexture;
}