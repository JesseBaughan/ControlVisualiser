#pragma once

namespace Engine
{
    class ImGuiRenderer
    {
    public:
        ImGuiRenderer();
        ~ImGuiRenderer();

        void OnUpdate();
    private:
        bool _show_demo_window;
    };
}