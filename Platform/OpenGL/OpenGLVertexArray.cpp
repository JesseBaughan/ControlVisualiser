#include "OpenGLVertexArray.h"

namespace Engine
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &_rendererID);
        glBindVertexArray(_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &_rendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(_rendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
    {
        //TODO:: ASSERT if the vertexBuffer.Geteleents() is 0

        glBindVertexArray(_rendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto &layout = vertexBuffer->GetLayout();
        for(auto& element: layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                element.GetComponentCount(), 
                GL_FLOAT, 
                element.Normalised ? GL_TRUE : GL_FALSE, 
                layout.GetStride(), 
                (const void*)element.Offset);

            index++;
        }

        _vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(_rendererID);
        indexBuffer->Bind();

        _indexBuffer = indexBuffer;
    }

} 
