#ifndef GLRESOURCE
#define GLRESOURCE

#include <vector>

class GlResource {
    friend class Engine;
public:
    GlResource();
    virtual ~GlResource() {};
private:
    static std::vector<GlResource*> resources;
    static void cleanup();
};

#endif /* GLRESOURCE */
