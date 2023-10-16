#include "Engine.h"
#include <iostream>

using namespace Engine;

class TestLayer : public Engine::Layer
{
public:
    TestLayer()
        : Layer("Test")
        , _camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
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

    void OnUpdate() override
    {
        RenderCommand::SetClearColour({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::Clear();

        //_camera.setPosition({0.8f, 0.8f, 0});
        static float rotation = 0;
        _camera.setRotation(rotation);
        rotation += 5.0f;

        Renderer::BeginScene(_camera);

        Renderer::Submit(_shader, _va);

        Renderer::EndScene();

    }

private:
    std::shared_ptr<Shader> _shader;
    std::shared_ptr<VertexArray> _va;

    OrthographicCamera _camera;
};

class Sandbox : public Engine::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestLayer());
    }
    
    ~Sandbox()
    {
    }
};

Engine::Application* Engine::CreateApplication()
{
    return new Sandbox();
}