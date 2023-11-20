#include "Core/Window.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "backends/imgui_impl_glfw.h"

namespace Engine
{

class LinuxWindow : public Window
{
    public:
        LinuxWindow(const WindowProperties &props);
        virtual ~LinuxWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return _width; }
        inline unsigned int GetHeight() const override { return _height; }
        virtual void* GetNativeWindow() const { return _window; };
        bool ShouldCloseWindow() const override;

    private:
        GLFWwindow* _window;
        GraphicsContext* _context;

        virtual void Init(const WindowProperties &props);
        virtual void Shutdown();
        void SetVSync(bool enabled);

        bool _show_demo_window{true};
        bool _GLFWwindowInitialised{false};
    
        unsigned int _width{0}; 
        unsigned int _height{0}; 
        std::string _title; 
};
    
} // namespace Engine