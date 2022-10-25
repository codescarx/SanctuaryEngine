#include "FFTWater.h"

#include <random>

static const float g = 9.81f;

float FFTWater::phillips(glm::vec2 k) {
    float L = (windspeed * windspeed) / g;
    float magk = glm::length(k);
    if (magk < 0.0001f) magk = 0.0001f;

    float numerator = expf(-1.f / (magk * magk * L * L));
    float denominator = magk * magk * magk * magk;
    float vectorstuff = powf(glm::dot(glm::normalize(k), glm::normalize(w)), 2.f);
    
    return A * (numerator / denominator) * vectorstuff;
}

std::complex<float> FFTWater::h0(glm::vec2 k) {
    std::normal_distribution<float> randGaussian(0.f, 1.f);
    std::mt19937 rng(0x1337);

    float common = (1.f / sqrtf(2.f)) * sqrtf(phillips(k));

    return std::complex<float>(common * randGaussian(rng), common * randGaussian(rng));
}

void FFTWater::precompute() {
    float *data = new float[N * N * 4];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float n = i - float(N) / 2.f;
            float m = j - float(N) / 2.f;
            //glm::vec2 x(n*length/float(N), m*length/float(N));
            glm::vec2 k(2.f * M_PI * n / length, 2 * M_PI * m / length);

            std::complex<float> h0k = h0(k);
            std::complex<float> h0minusk = h0(-k);

            data[4 * (i * N + j) + 0] = h0k.real();
            data[4 * (i * N + j) + 1] = h0k.imag();
            data[4 * (i * N + j) + 2] = h0minusk.real();
            data[4 * (i * N + j) + 3] = h0minusk.imag();
        }
    }

    h0Texture = new Texture(N, N, data);
    
    delete[] data;
}