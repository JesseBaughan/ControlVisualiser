#include "OpenGLBuffer.h"
#include "OpenGLContext.h"

namespace Engine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        //Generate 1 vertex buffer and assign the id to m_RendererID
        glGenBuffers(1, &_rendererID);
        //Bind our vertex buffer to GL_ARRAY_BUFFER variable - this is now active
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        //Bind the buffer to our data and tell it what size the data is
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); 
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &_rendererID);
    }

    void OpenGLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    }

    void OpenGLVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(float* data, unsigned int count)
        : _count(count) 
    {
        glGenBuffers(1, &_rendererID);
        //Bind our vertex buffer array to GL_ARRAY_BUFFER - this is now active
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); 
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
    }

    void OpenGLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    }

    void OpenGLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
} 
