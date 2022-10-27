#include "FFTWater.h"

#include <random>

static const float g = 9.81f;
static std::mt19937 rng(0x1337);

// copied from stanford bithacks
static unsigned bitrev(unsigned v) {
    // swap odd and even bits
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    // swap consecutive pairs
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    // swap nibbles ... 
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    // swap bytes
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    // swap 2-byte long pairs
    v = ( v >> 16             ) | ( v               << 16);
    return v;
}

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

    float common = (1.f / sqrtf(2.f)) * sqrtf(phillips(k));

    return std::complex<float>(common * randGaussian(rng), common * randGaussian(rng));
}

void FFTWater::precomputeH0k() {
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

            // data[4 * (j * N + i) + 0] = h0k.real();
            // data[4 * (j * N + i) + 1] = h0k.imag();
            // data[4 * (j * N + i) + 2] = h0minusk.real();
            // data[4 * (j * N + i) + 3] = h0minusk.imag();
        }
    }

    h0Texture = new Texture(N, N, data);
    
    delete[] data;
}

void FFTWater::precomputeButterfly() {
    float *data = new float[N * logN * 4];

    for (unsigned x = 0; x < logN; x++) {
        for (unsigned y = 0; y < N; y++) {
            float k = fmodf(float(y*N) / powf(2.f, x + 1), N);
            std::complex<float> twiddle(cos(2.f * M_PI * k / float(N)), sin(2.f * M_PI * k / float(N)));
            int span = 1 << x;

            bool top = (fmodf(y, powf(2.f, x + 1)) < span);

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

FFTWater::FFTWater(int N, float A, float windspeed, float length, const glm::vec2 &w) 
    : N(N), logN(log2(N)), A(A), windspeed(windspeed), length(length), w(w),
    hktCompute(N, length), ifft(N, logN)
{   
    precomputeH0k();
    precomputeButterfly();
}

void FFTWater::update() {
    hktCompute.compute(h0Texture);
    ifft.compute(hktCompute.hktTexture, butterflyTexture);
}