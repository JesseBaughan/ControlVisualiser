#pragma once

#include <string>

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    static unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int GetUniformLocation(const std::string& name);

    std::string m_filePath;
    unsigned int m_RendererID;
};