#include "../../Engine/src/Renderer/Renderer.h"

namespace Engine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() override;
        void Unbind() override;

    private:
        unsigned int _rendererID;
    }; 

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(float* vertices, uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() override;
        void Unbind() override;

        inline unsigned int GetCount() const { return _count; };

    private:
        unsigned int _rendererID;
        unsigned int _count;
    }; 
} 
