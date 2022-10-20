#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include <string>

class Shader {
public:
    Shader(const char *vert, const char *frag, const char *geom, const char *tessc, const char *tesse, const std::vector<std::string> &uniformVarNames);
    Shader(const char *compute, const std::vector<std::string> &uniformVarNames);
    virtual ~Shader();
    inline void use() { glUseProgram(programId); }
    inline void disuse() { glUseProgram(0); }
private:
    void addShader(const char *path, GLenum type);
    void link(const std::vector<std::string> &uniformVarNames);
    const GLuint programId;
    std::vector<GLuint> shaderIds;
    std::unordered_map<std::string, GLint> uniformLocs;
    const bool isCompute;
protected:

};

#endif /* SHADER */
