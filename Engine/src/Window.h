#pragma once

#include <string>

namespace Engine
{

struct WindowProperties
{
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProperties(const std::string& title = "Engine", 
                    unsigned int width = 1280, 
                    unsigned int height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

class Window
{
public:
    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void* GetNativeWindow() const = 0;

    virtual bool ShouldCloseWindow() const {}; 

    static Window* Create(const WindowProperties &props = WindowProperties());
};

}
