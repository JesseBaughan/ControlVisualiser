#include "shader.h"
#include "renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& filepath)
{

}

Shader::~Shader()
{

}

//TODO: use C++11 raw string literals 
Shader::ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = 1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream stringStream[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            stringStream[static_cast<int>(type)] << line << '\n';
        }
    }

    return { stringStream[0].str(), stringStream[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error handling
    int result;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        //TODO: Add debug output for each source type.
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //Combined both shaders into a single executable GPU shader programme
    glAttachShader(program, fs);
    glAttachShader(program, vs);
    glLinkProgram(program);

    int result;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteProgram(fs);
    glDeleteProgram(vs);

    return program;
}

void Shader::Bind() const
{

}

void Shader::Unbind() const
{

}

/*
// Set uniforms
void Shader::SetUniforms4f(const std:string& name, float v0, float v1, float f2, float f3) 
{

}
*/