#pragma once

#include <vector>

class Renderer;

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalised;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
        }

        //ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() 
        : m_Stride(0) {};

    template<typename T>
    struct failAssertion : std::false_type
    { };

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(failAssertion<T>::value);
	}

    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
    inline unsigned int GetStride() const { return m_Stride; };

private:
	std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}
