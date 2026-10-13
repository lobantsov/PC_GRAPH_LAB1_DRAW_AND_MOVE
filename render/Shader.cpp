#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << path << "\n";
        return {};
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::compile(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* code = source.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "ERROR::SHADER::COMPILE ("
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "):\n"
                  << log << "\n";
    }
    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    unsigned int vs = compile(GL_VERTEX_SHADER, readFile(vertexPath));
    unsigned int fs = compile(GL_FRAGMENT_SHADER, readFile(fragmentPath));

    id_ = glCreateProgram();
    glAttachShader(id_, vs);
    glAttachShader(id_, fs);
    glLinkProgram(id_);

    int success = 0;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        char log[1024];
        glGetProgramInfoLog(id_, sizeof(log), nullptr, log);
        std::cerr << "ERROR::PROGRAM::LINK:\n" << log << "\n";
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (id_) glDeleteProgram(id_);
}

void Shader::use() const {
    glUseProgram(id_);
}

int Shader::location(const std::string& name) const {
    return glGetUniformLocation(id_, name.c_str());
}

void Shader::setBool(const std::string& name, bool value) {
    use();
    glUniform1i(location(name), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) {
    use();
    glUniform1i(location(name), value);
}

void Shader::setFloat(const std::string& name, float value) {
    use();
    glUniform1f(location(name), value);
}

void Shader::setVec2(const std::string& name, float x, float y) {
    use();
    glUniform2f(location(name), x, y);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
    use();
    glUniform3f(location(name), x, y, z);
}