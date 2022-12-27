#include "src/Window.h"

#include "renderer.h"
#include "shader.h"

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

        private:
            GLFWwindow* _window;
            virtual void Init(const WindowProperties &props);
            virtual void Shutdown();

            bool _show_demo_window{true};
        
           unsigned int _width{0}; 
           unsigned int _height{0}; 
           std::string _title; 

           Shader *_shader;
           Renderer *_renderer;
           VertexArray *_va;
           VertexBuffer *_vb;
           VertexBufferLayout *_layout;
           IndexBuffer *_ib;
    };
    
} // namespace Engine