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
            case RendererAPI::None: return nullptr; 
            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        };

        return nullptr;
    }
} 
