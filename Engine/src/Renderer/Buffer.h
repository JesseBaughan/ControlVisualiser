#pragma once

#include <vector>
#include <stdint.h>
#include <string>

namespace Engine
{
    //TODO: add more types
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4
    };

    static unsigned int GetSizeOfType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
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
        bool Normalised;

        BufferElement() {};

        BufferElement(ShaderDataType type, const std::string& name)
            : Name(name)
            , Type(type)
            , Size(GetSizeOfType(type))
            , Offset(0)
            , Normalised(false) //TODO: pass this in as a default param.
        {
        }

        uint32_t GetComponentCount(ShaderDataType type) const
        {
            switch (type)
            {
                case ShaderDataType::Float3: return 3;
            }

            //TODO: Throw and assert.
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements) 
            : _elements(elements) 
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetElements() const { return _elements; };
        inline uint32_t GetStride() const { return _stride; };

        std::vector<BufferElement>::iterator begin() { return _elements.begin(); };
        std::vector<BufferElement>::iterator end() { return _elements.end(); };

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

        virtual void Bind() {};
        virtual void Unbind() {};

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

        virtual void Bind() {};
        virtual void Unbind() {};

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* data, unsigned int count);
    private:
        unsigned int m_RendererID;
    };

} 
