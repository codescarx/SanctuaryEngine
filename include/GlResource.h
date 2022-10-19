#ifndef GLRESOURCE
#define GLRESOURCE

#include <vector>

class GlResource {
    friend class Engine;
public:
    GlResource();
private:
    virtual ~GlResource();
    static std::vector<GlResource*> resources;
    static void cleanup();
};

#endif /* GLRESOURCE */
