#pragma once

#include "Engine/src/Renderer/RendererAPI.h" 

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

namespace Engine
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void SetClearColour(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
    };
} 

