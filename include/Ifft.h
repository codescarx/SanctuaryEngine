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
    void compute(Texture *hktTex, Texture *hktXTex, Texture *hktZTex, Texture *butterflyTex);
    inline Texture* getDxMap() { return dx; }
    inline Texture* getHeightmap() { return dy; }
    inline Texture* getDzMap() { return dz; }
private:
    const int N, logN;
    Texture *storage, *dx, *dy, *dz;
    Texture *ping, *pong;
    Ifft2 stage2;
};

#endif /* IFFT */
