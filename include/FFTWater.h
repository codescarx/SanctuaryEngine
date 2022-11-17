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
    FFTWater(int N, float A, float windspeed, float length, const glm::vec2 &w, float normalStrength);
    void update();

    inline Texture* getH0Texture() { return h0Texture; }
    inline Texture* getHktTexture() { return hktCompute.hktTexture; }
    inline Texture* getButterflyTexture() { return butterflyTexture; }
    inline Texture* getDxMap() { return ifft.getDxMap(); }
    inline Texture* getDzMap() { return ifft.getDzMap(); }
    inline Texture* getHeightmap() { return ifft.getHeightmap(); }
    inline Texture* getNormalmap() { return normalTex; }

    glm::vec3 position;
    glm::vec3 colour = glm::vec3(0.349, 0.384, 0.463);
    float tiling = 64.f, normalStrength, tessDivisor = 30.f;
    float heightScale = 1.5f, choppiness = 2.f;

    const int tileCnt = 128;
    const float tileSize = 12.5f;

    const int N, logN;
    const float A, windspeed, length;
    const glm::vec2 w;

    float reflectivity = 2.f, shineDamper = 280.0, fadeSpeed = 0.15f;
private:
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
