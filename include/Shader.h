#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    inline void loadFloat(const std::string &name, float f) {
        glUniform1f(uniformLocs[name], f);
    }

    inline void loadVec3(const std::string &name, const glm::vec3 &v) {
        glUniform3f(uniformLocs[name], v.x, v.y, v.z);
    }

    inline void loadMat4(const std::string &name, const glm::mat4 &m) {
        glUniformMatrix4fv(uniformLocs[name], 1, GL_FALSE, glm::value_ptr(m));
    }
};

#endif /* SHADER */
