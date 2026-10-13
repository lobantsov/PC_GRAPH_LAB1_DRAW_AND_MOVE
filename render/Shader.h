#ifndef LAB1_SHADER_H
#define LAB1_SHADER_H
#pragma once

#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, float x, float y, float z);

private:
    int location(const std::string& name) const;

    static std::string readFile(const std::string& path);
    static unsigned int compile(unsigned int type, const std::string& source);

    unsigned int id_ = 0;
};


#endif //LAB1_SHADER_H
