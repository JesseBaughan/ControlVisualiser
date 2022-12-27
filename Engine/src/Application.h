#pragma once

#include <memory>
#include "Window.h"
#include "ImGui/ImGuiRenderer.h"

namespace Engine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        static Application& Get() { return *_instance; }

        Window& GetWindow() { return *_window; }
    private:
         static Application* _instance;
         std::unique_ptr<Engine::Window> _window;
         std::unique_ptr<Engine::ImGuiRenderer> _imgui;
    };

    //To be defined in CLIENT
    Application* CreateApplication();
}