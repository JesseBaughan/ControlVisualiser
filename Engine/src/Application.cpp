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
        _va.reset(VertexArray::Create());

        float vehicle_vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.6f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.6f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.3f, 0.2f, 0.6f, 1.0f
        };
        
        _vb.reset(VertexBuffer::Create(vehicle_vertices, sizeof(vehicle_vertices)));

        BufferLayout layout = { {ShaderDataType::Float3, "a_Position"},
                                {ShaderDataType::Float4, "a_Colour"}};
        _vb->SetLayout(layout);
        _va->AddVertexBuffer(_vb);

        uint32_t indices[3] = {0, 1, 3};  
        _ib.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        _va->SetIndexBuffer(_ib);

        std::string vertexSource = R"(
            #version 330

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Colour;

            out vec3 v_Position;
            out vec4 v_Colour;

            void main() 
            {
                v_Position = a_Position;
                v_Colour = a_Colour;
                gl_Position = vec4(a_Position, 1.0);
            };
        )";

        std::string fragmentSource = R"(
            #version 330

            layout(location = 0) out vec4 colour;

            in vec3 v_Position;
            in vec4 v_Colour;

            void main() 
            {
                colour = vec4(v_Position * 0.5 + 0.5 , 1.0);
                colour = v_Colour;
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
            transformation = transformation; 
            //_shader->SetUniformMat4f("u_MVP", transformation);
            
            _va->Bind();
            glDrawElements(GL_TRIANGLES, _ib->GetCount(), GL_UNSIGNED_INT, 0);

            _shader->Unbind();

            _imgui->End();

            _window->OnUpdate();
        }
    }
}