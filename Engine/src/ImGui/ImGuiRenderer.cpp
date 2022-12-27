#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ImGuiRenderer.h"

namespace Engine
{
    ImGuiRenderer::ImGuiRenderer(GLFWwindow *window)
    {
        Init(window);
    }

    ImGuiRenderer::~ImGuiRenderer()
    {
    }

    void ImGuiRenderer::Init(GLFWwindow *window)
    {
        const char* glsl_version = "#version 130";
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImGuiRenderer::OnUpdate()
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&_show_demo_window);

        // Rendering of ImGui
        ImGui::Render();
    }
}