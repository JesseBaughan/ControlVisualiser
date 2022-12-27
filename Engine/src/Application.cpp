#include <stdio.h>
#include <iostream>
#include <math.h>
#include <memory>

#include "src/Window.h"
#include "src/ImGui/ImGuiRenderer.h"
#include "Application.h"

namespace Engine
{
    Application::Application()
    {

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        std::unique_ptr<Engine::Window> window = std::unique_ptr<Engine::Window>(Engine::Window::Create());

        bool _running = true;
        while (_running)
        {
            window->OnUpdate();
        }
    }
}