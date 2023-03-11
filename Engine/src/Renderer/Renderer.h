#pragma once

#include <GL/gl3w.h>
#include "Buffer.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"

namespace Engine 
{
    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
    public:
        virtual void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const = 0;
        virtual void Clear() const = 0;
        inline static RendererAPI GetAPI() { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;
    };
}