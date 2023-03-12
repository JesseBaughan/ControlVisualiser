#include "Buffer.h"
#include "vertex_array.h"

namespace Engine
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
    {
        Bind();
        vb.Bind();
        const auto&  elements = layout.GetElements();
        unsigned int offset = 0;
        for(unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            //Vertex 0 (first argument) will use vertex at GL_ARRAY_BUFFER location
            //which was set to vbo location previously
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.GetComponentCount(), GL_FLOAT, 
                                  element.Normalised ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
        }
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }
}