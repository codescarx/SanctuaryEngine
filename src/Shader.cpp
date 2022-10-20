#include "Shader.h"

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

Shader::Shader(const char *vert, const char *frag, const char *geom, const char *tessc, const char *tesse, const std::vector<std::string> &uniformVarNames) : programId(glCreateProgram()), isCompute(false) {
    if (vert) addShader(vert, GL_VERTEX_SHADER);
    if (frag) addShader(frag, GL_FRAGMENT_SHADER);
    if (geom) addShader(geom, GL_GEOMETRY_SHADER);
    if (tessc) addShader(tessc, GL_TESS_CONTROL_SHADER);
    if (tesse) addShader(tesse, GL_TESS_EVALUATION_SHADER);
    link(uniformVarNames);
}

Shader::Shader(const char *compute, const std::vector<std::string> &uniformVarNames) : programId(glCreateProgram()), isCompute(true) {
    addShader(compute, GL_COMPUTE_SHADER);
    link(uniformVarNames);
}

void Shader::link(const std::vector<std::string> &uniformVarNames) {
    glLinkProgram(programId);
    glValidateProgram(programId);

    for (GLuint sid : shaderIds) {
        glDetachShader(programId, sid);
        glDeleteShader(sid);
    }
    shaderIds.clear();

    for (const std::string &name : uniformVarNames) {
        uniformLocs[name] = glGetUniformLocation(programId, name.c_str());
    }
}

Shader::~Shader() {
    disuse();
    glDeleteProgram(programId);
}

void Shader::addShader(const char *path, GLenum type) {
    FILE *f = fopen(path, "r");
    if (f == NULL) fatal("bad shader path");

    fseek(f, 0, SEEK_END);
    GLint fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *source = new char[fsize];
    fread(source, fsize, 1, f);
    fclose(f);

    GLuint shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &source, &fsize);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        char log[512];
        glGetShaderInfoLog(shaderId, 512, NULL, log);
        puts(log);
        fatal("fatal: failed to compile shader");
    }

    delete[] source;

    shaderIds.push_back(shaderId);
    glAttachShader(programId, shaderId);
}