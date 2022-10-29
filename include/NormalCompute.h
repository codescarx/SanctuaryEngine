#ifndef NORMALCOMPUTE
#define NORMALCOMPUTE

#include "Shader.h"
#include "Texture.h"

class NormalCompute : public Shader {
public:
    NormalCompute();
    void compute(int N, Texture *heightTex, float strength, Texture *normalTex);
    void compute(int N, GLuint heightTex, float strength, GLuint normalTex);
};

#endif /* NORMALCOMPUTE */
