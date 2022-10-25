#ifndef HKTCOMPUTE
#define HKTCOMPUTE

#include "Shader.h"
#include "Texture.h"

class HktCompute : public Shader {
public:
    HktCompute(int N, float length, Texture *h0Texture);
    Texture* compute();
private:
    const int N;
    Texture * const h0Texture;
    Texture * const hktTexture;
    float t = 0.f;
};

#endif /* HKTCOMPUTE */
