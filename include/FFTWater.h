#ifndef FFTWATER
#define FFTWATER

#include <glm/glm.hpp>
#include <complex>

#include "Texture.h"
#include "HktCompute.h"
#include "Ifft.h"
#include "NormalCompute.h"

class FFTWater {
public:
    FFTWater(int N, float A, float windspeed, float length, const glm::vec2 &w);
    void update();

    inline Texture* getH0Texture() { return h0Texture; }
    inline Texture* getHktTexture() { return hktCompute.hktTexture; }
    inline Texture* getButterflyTexture() { return butterflyTexture; }
    inline Texture* getHeightmap() { return ifft.getHeightmap(); }
    inline Texture* getNormalmap() { return normalTex; }
private:
    const int N, logN;
    const float A, windspeed, length;
    const glm::vec2 w;

    HktCompute hktCompute;
    Ifft ifft;
    NormalCompute normalCompute;

    Texture *h0Texture, *butterflyTexture, *normalTex;

    unsigned bitrev(unsigned u);
    void precomputeH0k();
    void precomputeButterfly();
    float phillips(glm::vec2 k);
    std::complex<float> h0(glm::vec2 k);
};

#endif /* FFTWATER */
