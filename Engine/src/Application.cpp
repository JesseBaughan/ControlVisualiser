#include <stdio.h>
#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"
#include "Renderer/Renderer.h"
#include <unistd.h>

namespace Engine
{

// TODO: replace with better singleton creation pattern.
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

void Application::PushLayer(Layer* layer)
{
    _layerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* overlay)
{
    _layerStack.PushLayer(overlay);
}

void Application::Run()
{
    while (!_window->ShouldCloseWindow())
    {
        _imgui->Begin();

        for(Layer* layer : _layerStack)
        {
            layer->OnUpdate();
        }

        _imgui->End();

        _window->OnUpdate();

        usleep(10000);
    }
}

}