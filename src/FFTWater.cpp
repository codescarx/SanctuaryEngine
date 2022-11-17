#include "FFTWater.h"

#include "util.h"
#include <math.h>
#include <random>

static const float g = 9.81f;
static std::mt19937 rng(0x13376969);

float FFTWater::phillips(glm::vec2 k) {
    float L = (windspeed * windspeed) / g;
    float magk = glm::length(k);
    if (magk < 0.0001f) magk = 0.0001f;

    float numerator = expf(-1.f / (magk * magk * L * L));
    float denominator = magk * magk * magk * magk;
    float vectorstuff = powf(fabsf(glm::dot(k / magk, glm::normalize(w))), 4.f); 
 
    return A * (numerator / denominator) * vectorstuff * exp(-(magk * magk) * (1.f * 1.f));
}

std::complex<float> FFTWater::h0(glm::vec2 k) {
    std::normal_distribution<float> randGaussian(0.f, 1.f);

    float common = sqrtf(phillips(k)) / sqrtf(2.f);

    return std::complex<float>(common * randGaussian(rng), common * randGaussian(rng));
}

void FFTWater::precomputeH0k() {
    float *data = new float[N * N * 4];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float n = i - float(N) / 2.f;
            float m = j - float(N) / 2.f;
            glm::vec2 k(2.f * M_PI * n / length, 2.f * M_PI * m / length);

            std::complex<float> h0k = h0(k);
            std::complex<float> h0minusk = h0(-k);

            // data[4 * (i * N + j) + 0] = h0k.real();
            // data[4 * (i * N + j) + 1] = h0k.imag();
            // data[4 * (i * N + j) + 2] = h0minusk.real();
            // data[4 * (i * N + j) + 3] = h0minusk.imag();

            data[4 * (j * N + i) + 0] = h0k.real();
            data[4 * (j * N + i) + 1] = h0k.imag();
            data[4 * (j * N + i) + 2] = h0minusk.real();
            data[4 * (j * N + i) + 3] = h0minusk.imag();
        }
    }

    h0Texture = new Texture(N, N, data);
    
    delete[] data;
}

unsigned FFTWater::bitrev(unsigned u) {
    assert(u < (1 << logN));
    unsigned res = 0;
    for (int i = 0; i < logN; i++) {
        if ((u >> i) & 1) {
            res |= (1 << (logN - 1 - i));
        }
    }
    return res;
}

void FFTWater::precomputeButterfly() {
    float *data = new float[N * logN * 4];

    for (unsigned x = 0; x < logN; x++) {
        for (unsigned y = 0; y < N; y++) {
            float k = fmodf(float(y*N) / powf(2.f, x + 1), N);
            std::complex<float> twiddle(cosf(2.f * M_PI * k / float(N)), sinf(2.f * M_PI * k / float(N)));
            int span = int(powf(2.f, x));

            bool top = (fmodf(y, powf(2.f, x + 1)) < powf(2.f, x));

            unsigned idx1, idx2;
            if (x == 0) { // first stage with bit reversed indices
                if (top) {
                    idx1 = bitrev(y);
                    idx2 = bitrev(y + 1);
                }
                else {
                    idx1 = bitrev(y - 1);
                    idx2 = bitrev(y);
                }
            }
            else {
                if (top) {
                    idx1 = y;
                    idx2 = y + span;
                }
                else {
                    idx1 = y - span;
                    idx2 = y;
                }
            }

            // data[4 * (x * N + y) + 0] = twiddle.real();
            // data[4 * (x * N + y) + 1] = twiddle.imag();
            // data[4 * (x * N + y) + 2] = idx1;
            // data[4 * (x * N + y) + 3] = idx2;

            data[4 * (y * logN + x) + 0] = twiddle.real();
            data[4 * (y * logN + x) + 1] = twiddle.imag();
            data[4 * (y * logN + x) + 2] = idx1;
            data[4 * (y * logN + x) + 3] = idx2;
        }
    }

    butterflyTexture = new Texture(logN, N, data);

    delete[] data;
}

FFTWater::FFTWater(int N, float A, float windspeed, float length, const glm::vec2 &w, float normalStrength) 
    : N(N), logN(log2(N)), A(A), windspeed(windspeed), length(length), w(w), normalStrength(normalStrength),
    hktCompute(N, length), ifft(N, logN)
{   
    precomputeH0k();
    precomputeButterfly();
    normalTex = new Texture(N, N, nullptr, GL_LINEAR);
}

void FFTWater::update() {
    hktCompute.compute(h0Texture);
    ifft.compute(hktCompute.hktTexture, hktCompute.hktXTexture, hktCompute.hktZTexture, butterflyTexture);
    normalCompute.compute(N, ifft.getHeightmap(), normalStrength, normalTex);
}
