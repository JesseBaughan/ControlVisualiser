#pragma once

#include <memory>
#include "Window.h"
#include "ImGui/ImGuiRenderer.h"

namespace Engine
{
    class Application
    {
    public:
        virtual ~Application();

        //Singletons should not have copy constructor
        Application(Application& other) = delete;

        //Singletons should not have copy assignment constructor
        void operator=(const Application&) = delete;

        void Run();

        static Application& Get() { return *_instance; }

        Window& GetWindow() { return *_window; }
    protected:
        //Singletons constuctor should be protected to avoid direct construction using new keyword.
         Application();
    private:
         static Application* _instance;
         std::unique_ptr<Engine::Window> _window;
         std::unique_ptr<Engine::ImGuiRenderer> _imgui;
    };

    //To be defined in CLIENT
    Application* CreateApplication();
}