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

        _va.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.6f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.3f, 0.2f, 0.6f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.3f, 0.2f, 0.6f, 1.0f
        };
        
        std::shared_ptr<VertexBuffer> _vb;
        _vb.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = { {ShaderDataType::Float3, "a_Position"},
                                {ShaderDataType::Float4, "a_Colour"}};
        _vb->SetLayout(layout);
        _va->AddVertexBuffer(_vb);

        uint32_t indices[3] = {0, 1, 2};  
        std::shared_ptr<IndexBuffer> _ib;
        _ib.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        _va->SetIndexBuffer(_ib);

        _shader = std::make_shared<Shader>("../SandBox/assets/shaders/Basic.shader");
    }

    void Application::Run()
    {
        while (!_window->ShouldCloseWindow())
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
            glDrawElements(GL_TRIANGLES, _va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

            _imgui->End();

            _window->OnUpdate();
        }
    }
}