#include <stdio.h>
#include <iostream>
#include <math.h>

#include "Application.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Renderer.h"

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
            RenderCommand::SetClearColour({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();

            _imgui->Begin();

            Renderer::BeginScene();

            _shader->Bind();

            Renderer::Submit(_va);

            Renderer::EndScene();

            _imgui->End();

            _window->OnUpdate();
        }
    }
}