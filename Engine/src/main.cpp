#include <stdio.h>
#include <iostream>
#include <math.h>
#include <memory>

#include "src/Window.h"

int main(int, char**)
{
    std::unique_ptr<Engine::Window> window = std::unique_ptr<Engine::Window>(Engine::Window::Create());

    bool _running = true;
    while (_running)
    {
        window->OnUpdate();
    }

    return 0;
}