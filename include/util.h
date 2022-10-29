#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <glm/glm.hpp>

inline void fatal(const char *message) {
    puts(message);
    exit(1);
}

inline std::ostream& operator<<(std::ostream &os, const glm::vec2 &v) {
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}
inline std::ostream& operator<<(std::ostream &os, const glm::vec3 &v) {
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
}