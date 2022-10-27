#ifndef IFFT
#define IFFT

#include "Shader.h"
#include "Texture.h"

class Ifft2 : public Shader {
public:
    Ifft2(int N);
    void compute(Texture *in, Texture *out);
private:
    const int N;
};

class Ifft : public Shader {
public:
    Ifft(int N, int logN);
    void compute(Texture *hktTex, Texture *butterflyTex);
    inline Texture* getHeightmap() { return pong; }
private:
    const int N, logN;
    Texture *storage;
    Texture *ping, *pong;
    Ifft2 stage2;
};

#endif /* IFFT */
