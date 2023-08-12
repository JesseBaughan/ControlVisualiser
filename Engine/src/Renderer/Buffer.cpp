#include "Renderer.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{
    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                return nullptr;
            break;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
            break;
        };

        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                return nullptr;
            break;
            case RendererAPI::API::OpenGL:
                return new OpenGLIndexBuffer(indices, size);
            break;
        };

        return nullptr;
    }
} 
