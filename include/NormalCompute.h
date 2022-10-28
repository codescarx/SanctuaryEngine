#ifndef NORMALCOMPUTE
#define NORMALCOMPUTE

#include "Shader.h"
#include "Texture.h"

class NormalCompute : public Shader {
public:
    NormalCompute();
    void compute(int N, Texture *heightTex, float amplitude, Texture *normalTex);
    void compute(int N, GLuint heightTex, float amplitude, GLuint normalTex);
};

#endif /* NORMALCOMPUTE */
