#include "Engine.h"
#include <iostream>

class TestLayer : public Engine::Layer
{
public:
    TestLayer()
        : Layer("Test")
    {
    }

    void OnUpdate() override
    {
        std::cout << "TESTING TESTING, 1 , 2, 3!";
    }
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