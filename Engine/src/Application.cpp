#include <stdio.h>
#include <iostream>
#include <math.h>

#include "ImGui/ImGuiRenderer.h"
#include "Application.h"
//#include "Glyph/Triangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    Application* Application::_instance = nullptr;

    Application::Application()
    {
        if(_instance != nullptr)
        {
            return;
        }
		_instance = this;

        _window = std::unique_ptr<Engine::Window>(Engine::Window::Create());
        _imgui = std::unique_ptr<Engine::ImGuiRenderer>(new Engine::ImGuiRenderer());
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        unsigned int m_RendererID;
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);

        float vehicle_vertices[9] = {
            -0.1f, -0.3f, 0.0f, //0
            0.1f, -0.3f, 0.0f,  //1
            0.0f,  0.3f, 0.0f   //2
        };
        
        _vb.reset(VertexBuffer::Create(vehicle_vertices, 9 * sizeof(float)));

        BufferLayout layout = { {ShaderDataType::Float3, "a_Position"} };

        const auto&  elements = layout.GetElements();
        for(unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            //Vertex 0 (first argument) will use vertex at GL_ARRAY_BUFFER location
            //which was set to vbo location previously
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, 
                element.GetComponentCount(), GL_FLOAT, 
                element.Normalised ? GL_TRUE : GL_FALSE, 
                layout.GetStride(), 
                (const void*)element.Offset);
        }
        
        uint32_t indices[3] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
        };  

        _ib.reset(IndexBuffer::Create(indices, 3));
        
        std::string vertexSource = R"(
            #version 330

            in vec3 vp;

            uniform mat4 u_MVP;

            void main() 
            {
            gl_Position = u_MVP * vec4(vp, 1.0);
            };
        )";

        std::string fragmentSource = R"(
            #version 330

            out vec4 frag_colour;

            void main() 
            {
            frag_colour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            };
        )";

        //_shader.reset(new Shader("Basic.shader"));
        _shader.reset(new Shader(vertexSource, fragmentSource));

        bool _running = true;
        while (_running)
        {
            glClearColor(0.1f,  0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            _imgui->Begin();

            //Rendering of test triangle
            _shader->Bind();
            //Rotate 90degrees about z-axis
            glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
            //Translate by some X/Y amount
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
            glm::mat4 transformation = translation * rotate;
            //float aspect = window->GetWidth()/window->GetHeight();
            //Ensure our shape is being kept at the right scaling even with window size changing
            //glm::mat4 proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
            //Re-scale for window size change to keep proper shape proportions
            //transformation = proj * transformation; 
            _shader->SetUniformMat4f("u_MVP", transformation);

            glBindVertexArray(m_RendererID);
            _ib->Bind();
            glDrawElements(GL_TRIANGLES, _ib->GetCount(), GL_UNSIGNED_INT, 0);
            _shader->Unbind();

            _imgui->End();

            _window->OnUpdate();
        }
    }
}