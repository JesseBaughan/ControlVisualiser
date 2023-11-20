#include "Platform/Linux/LinuxWindow.h"

#define PLATFORM_LINUX

namespace Engine
{

Window* Window::Create(const WindowProperties& props)
{
    #ifdef PLATFORM_LINUX
        return new LinuxWindow(props);
    #endif

    return nullptr;
}

}