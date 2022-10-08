#pragma once

#include <string>

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniforms4f(const std::string& name, float v0, float v1, float f2, float f3);

    struct ShaderProgramSource
    {
        std::string VertexShader;
        std::string FragmentShader;
    };

    static ShaderProgramSource ParseShader(const std::string& filepath);
    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int GetUniformLocation(const std::string& name);
};