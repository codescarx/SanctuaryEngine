#ifndef HKTCOMPUTE
#define HKTCOMPUTE

#include "Shader.h"
#include "Texture.h"

class HktCompute : public Shader {
public:
    HktCompute(int N, float length);
    void compute(Texture *h0Texture);
    Texture * const hktTexture;
    Texture * const hktXTexture;
    Texture * const hktZTexture;
private:
    const int N;
    float t = 0.f;
};

#endif /* HKTCOMPUTE */
