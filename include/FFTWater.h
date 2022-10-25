#ifndef FFTWATER
#define FFTWATER

#include <glm/glm.hpp>
#include <complex>

class FFTWater {
public:
private:
    const float A, windspeed, length;
    const glm::vec2 w;
    const int N;

    void precompute();
    float phillips(glm::vec2 k);
    std::complex<float> h0(glm::vec2 k);
};

#endif /* FFTWATER */
