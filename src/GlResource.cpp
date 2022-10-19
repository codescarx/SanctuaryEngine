#include "GlResource.h"

std::vector<GlResource*> GlResource::resources;

GlResource::GlResource() {
    resources.push_back(this);
}

void GlResource::cleanup() {
    for (GlResource *res : resources) {
        delete res;
    }
}