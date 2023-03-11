#include <stdio.h>
#include <iostream>
#include <math.h>

#include "ImGui/ImGuiRenderer.h"
#include "Application.h"
#include "Glyph/Triangle.h"

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
        Engine::TriangleGlyph glyph = Engine::TriangleGlyph();

        bool _running = true;
        while (_running)
        {
            glClearColor(0.45f,  0.55f, 0.6f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            _imgui->Begin();
            glyph.Draw(_window.get());
            _imgui->End();

            _window->OnUpdate();
        }
    }
}