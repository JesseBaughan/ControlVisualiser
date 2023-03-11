#pragma once

namespace Engine
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static IndexBuffer* Create(float* data, unsigned int count);
        inline unsigned int GetCount() const { return m_Count; };

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    }; 

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static VertexBuffer* Create(float* data, unsigned int count);

    private:
        unsigned int m_RendererID;
    };
} 
