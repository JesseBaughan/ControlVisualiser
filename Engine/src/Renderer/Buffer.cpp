#include "Renderer.h"
#include "Buffer.h"

//TODO: fix this include path so not relative.
#include "../../Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:
                return nullptr;
            break;
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            break;
        };

        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(float* indices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::None:
                return nullptr;
            break;
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, size);
            break;
        };

        return nullptr;
    }
} 
