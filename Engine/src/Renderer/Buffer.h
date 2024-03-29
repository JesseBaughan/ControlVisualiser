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
        case ShaderDataType::Float:  return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::None:   break;
    }

    //ASSERT(false, "Unknown shader type!");
    return 0;
}

struct BufferElement
{
    std::string Name;
    ShaderDataType Type;
    uint32_t Size;
    int Offset;
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

    int GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::None:      break;
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
    std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); };
    std::vector<BufferElement>::const_iterator end() const { return _elements.end(); };

private:
    void CalculateOffsetsAndStride()
    {
        int offset = 0;
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

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static IndexBuffer* Create(uint32_t* data, unsigned int count);
    virtual int GetCount() const = 0;
}; 

class VertexBuffer
{
public:
    virtual ~VertexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetLayout(const BufferLayout& layout) = 0;
    virtual const BufferLayout& GetLayout() const = 0;

    static VertexBuffer* Create(float* data, unsigned int count);
};

} 
