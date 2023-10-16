#pragma once

#include "Window.h"
#include "ImGui/ImGuiRenderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "OrthographicCamera.h"
#include "LayerStack.h"

namespace Engine
{

class Application
{
public:
    virtual ~Application() {};

    // Singletons should not have copy constructor
    Application(Application& other) = delete;

    // Singletons should not have copy assignment constructor
    void operator=(const Application&) = delete;

    void Run();

    static Application& Get() { return *_instance; }

    Window& GetWindow() { return *_window; }

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

protected:
    // Singletons constuctor should be protected to avoid direct construction using new keyword.
    Application();

private:
    static Application* _instance;
    std::unique_ptr<Engine::Window> _window;
    std::unique_ptr<Engine::ImGuiRenderer> _imgui;


    LayerStack _layerStack;
};

//To be defined in CLIENT
Application* CreateApplication();

}