#include "Ifft.h"

#include <algorithm>

Ifft2::Ifft2(int N) : N(N), Shader("res/shader/ifft2.comp", {"N"}) {}

void Ifft2::compute(Texture *in, Texture *out) {
    use();
    loadInt("N", N);
    in->bindImage(0, GL_READ_ONLY);
    out->bindImage(1, GL_WRITE_ONLY);
    dispatchCompute(N/16, N/16, 1);
    disuse();
} 

// ==================================================

Ifft::Ifft(int N, int logN) :
    N(N), logN(logN), storage(new Texture(N, N, nullptr)), dx(new Texture(N, N, nullptr)), dy(new Texture(N, N, nullptr)), dz(new Texture(N, N, nullptr)), stage2(N),
    Shader("res/shader/ifft.comp", {"stage", "horiz"}) {}

void Ifft::compute(Texture *hktTex, Texture *hktXTex, Texture *hktZTex, Texture *butterflyTex) {
    
    
    {
        use();
        butterflyTex->bindImage(0, GL_READ_ONLY);

        pong = hktTex, ping = storage;

        loadInt("horiz", 1);

        for (int i = 0; i < logN; i++) {
            std::swap(ping, pong);
            ping->bindImage(1, GL_READ_ONLY);
            pong->bindImage(2, GL_WRITE_ONLY);
            loadInt("stage", i);
            dispatchCompute(N/16, N/16, 1);
        }

        loadInt("horiz", 0);
        for (int i = 0; i < logN; i++) {
            std::swap(ping, pong);
            ping->bindImage(1, GL_READ_ONLY);
            pong->bindImage(2, GL_WRITE_ONLY);
            loadInt("stage", i);
            dispatchCompute(N/16, N/16, 1);
        }

        std::swap(ping, pong);
        stage2.compute(ping, dy);
    }

    {
        use();
        butterflyTex->bindImage(0, GL_READ_ONLY);

        pong = hktXTex, ping = storage;

        loadInt("horiz", 1);

        for (int i = 0; i < logN; i++) {
            std::swap(ping, pong);
            ping->bindImage(1, GL_READ_ONLY);
            pong->bindImage(2, GL_WRITE_ONLY);
            loadInt("stage", i);
            dispatchCompute(N/16, N/16, 1);
        }

        loadInt("horiz", 0);
        for (int i = 0; i < logN; i++) {
            std::swap(ping, pong);
            ping->bindImage(1, GL_READ_ONLY);
            pong->bindImage(2, GL_WRITE_ONLY);
            loadInt("stage", i);
            dispatchCompute(N/16, N/16, 1);
        }

        std::swap(ping, pong);
        stage2.compute(ping, dx);
    }

    {
        use();
        butterflyTex->bindImage(0, GL_READ_ONLY);

        pong = hktZTex, ping = storage;

        loadInt("horiz", 1);

        for (int i = 0; i < logN; i++) {
            std::swap(ping, pong);
            ping->bindImage(1, GL_READ_ONLY);
            pong->bindImage(2, GL_WRITE_ONLY);
            loadInt("stage", i);
            dispatchCompute(N/16, N/16, 1);
        }

        loadInt("horiz", 0);
        for (int i = 0; i < logN; i++) {
            std::swap(ping, pong);
            ping->bindImage(1, GL_READ_ONLY);
            pong->bindImage(2, GL_WRITE_ONLY);
            loadInt("stage", i);
            dispatchCompute(N/16, N/16, 1);
        }

        std::swap(ping, pong);
        stage2.compute(ping, dz);
    }

    disuse();
}