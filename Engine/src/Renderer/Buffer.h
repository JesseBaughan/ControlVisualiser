#pragma once

#include <vector>
#include <stdint.h>
#include <string>

namespace Engine
{
    //TODO: add more types
    enum class ShaderDataType
    {
        None = 0, Float
    };

    static unsigned int GetSizeOfType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return 4;
        }

        //ASSERT(false, "Unknown shader type!");
        return 0;
    }

    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;

        BufferElement(ShaderDataType type, const std::string& name)
            : Name(name)
            , Type(type)
            , Size(GetSizeOfType(type))
            , Offset(0)
        {
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout(const std::initializer_list<BufferElement>& elements) 
            : _elements(elements) 
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetElements() const { return _elements; };
        inline uint32_t GetStride() const { return _stride; };

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            _stride = 0;

            for(auto& element: _elements)
            {
                element.Offset = offset;
                offset += element.Size;
                _stride += element.Size;
            }
        }

        std::vector<BufferElement> _elements;
        uint32_t _stride{0};
    };

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

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* data, unsigned int count);
    private:
        unsigned int m_RendererID;
    };

} 
