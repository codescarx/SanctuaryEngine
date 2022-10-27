#include "Ifft.h"

#include <algorithm>

Ifft2::Ifft2(int N) : N(N), Shader("res/shader/ifft2.comp", {"N"}) {}

void Ifft2::compute(Texture *in, Texture *out) {
    use();
    loadInt("N", N);
    in->bindImage(0, GL_READ_ONLY);
    out->bindImage(1, GL_WRITE_ONLY);
    glDispatchCompute(N/16, N/16, 1);
    disuse();
} 

// ==================================================

Ifft::Ifft(int N, int logN) :
    N(N), logN(logN), storage(new Texture(N, N, nullptr)), stage2(N),
    Shader("res/shader/ifft.comp", {"stage", "horiz"}) {}

void Ifft::compute(Texture *hktTex, Texture *butterflyTex) {
    pong = hktTex, ping = storage;
    
    use();
    butterflyTex->bindImage(0, GL_READ_ONLY);

    loadInt("horiz", 1);
    for (int i = 0; i < logN; i++) {
        std::swap(ping, pong);
        ping->bindImage(1, GL_READ_ONLY);
        pong->bindImage(2, GL_WRITE_ONLY);
        loadInt("stage", i);
        glDispatchCompute(N/16, N/16, 1);
    }

    loadInt("horiz", 0);
    for (int i = 0; i < logN; i++) {
        std::swap(ping, pong);
        ping->bindImage(1, GL_READ_ONLY);
        pong->bindImage(2, GL_WRITE_ONLY);
        loadInt("stage", i);
        glDispatchCompute(N/16, N/16, 1);
    }

    disuse();

    std::swap(ping, pong);
    stage2.compute(ping, pong);
}