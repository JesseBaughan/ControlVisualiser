
#include "LinuxWindow.h"

namespace Engine
{
    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    LinuxWindow::LinuxWindow(const WindowProperties &props)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        Shutdown();
    }

    void LinuxWindow::Shutdown()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void LinuxWindow::Init(const WindowProperties &props)
    {
        //TODO: put this is a struct that is for storing this type of window data.
        _width = props.Width;
        _height = props.Height;
        _title = props.Title;

        if(!_GLFWwindowInitialised)
        {
            int success = glfwInit();
            //TODO: output something to tell us if successful.
            glfwSetErrorCallback(glfw_error_callback);
            _GLFWwindowInitialised = true;
        }

        // Create window with graphics context
        //TODO: use the window struct data to set the window size rather than hardcoded values.
        _window = glfwCreateWindow(_width, _height, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
        if (_window == NULL)
        {
            return;
        }

        _context = new OpenGLContext(_window);
        _context->Init();

        SetVSync(true);
    }

    void LinuxWindow::OnUpdate()
    {
        _context->SwapBuffers();
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        if(enabled)
        {
            glfwSwapInterval(1); 
        }
        else
        {
            glfwSwapInterval(0); 
        }
    }
}