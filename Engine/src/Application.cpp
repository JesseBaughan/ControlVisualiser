#include <stdio.h>
#include <iostream>
#include <math.h>

#include "src/ImGui/ImGuiRenderer.h"
#include "Application.h"

namespace Engine
{
    Application* Application::_instance = nullptr;

    Application::Application()
    {
		_instance = this;
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        _window = std::unique_ptr<Engine::Window>(Engine::Window::Create());
        _imgui = std::unique_ptr<Engine::ImGuiRenderer>(new Engine::ImGuiRenderer());

        bool _running = true;
        while (_running)
        {
            _imgui->Begin();
            _imgui->End();

            _window->OnUpdate();
        }
    }
}