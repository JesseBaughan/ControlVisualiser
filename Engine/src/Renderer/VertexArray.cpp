#include "Renderer.h"
#include "VertexArray.h"

//TODO: fix this include path so not relative.
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None: return nullptr; 
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        };

        return nullptr;
    }
} 
