#include "../../Engine/src/Renderer/Buffer.h"

namespace Engine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() override;
        void Unbind() override;

        virtual const BufferLayout& GetLayout() const override { return _layout; }
        virtual void SetLayout(const BufferLayout& layout) override { _layout = layout; }

    private:
        unsigned int _rendererID;
        BufferLayout _layout;
    }; 

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() override;
        void Unbind() override;

        inline unsigned int GetCount() const { return _count; };

    private:
        unsigned int _rendererID;
        unsigned int _count;
    }; 
} 