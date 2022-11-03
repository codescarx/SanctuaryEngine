#include "HktCompute.h"

#include "Engine.h"

HktCompute::HktCompute(int N, float length)
    : N(N), hktTexture(new Texture(N, N, nullptr)), hktXTexture(new Texture(N, N, nullptr)), hktZTexture(new Texture(N, N, nullptr)),
    Shader("res/shader/hkt.comp", {"N", "L", "t"})
{
    use();
    loadInt("N", N);
    loadFloat("L", length);
    disuse();
}

void HktCompute::compute(Texture *h0Texture) {
    use();
    t += Engine::instance->getDelta() * 1.f;
    loadFloat("t", t);

    h0Texture->bindImage(0, GL_READ_ONLY);
    hktTexture->bindImage(1, GL_WRITE_ONLY);
    hktXTexture->bindImage(2, GL_WRITE_ONLY);
    hktZTexture->bindImage(3, GL_WRITE_ONLY);

    glDispatchCompute(N/16, N/16, 1);
    disuse();
}