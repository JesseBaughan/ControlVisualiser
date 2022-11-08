#include "vertex_buffer.h"

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //Generate 1 vertex buffer and assign the id to m_RendererID
    glGenBuffers(1, &m_RendererID);
    //Bind our vertex buffer to GL_ARRAY_BUFFER variable - this is now active
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //Bind the buffer to our data and tell it what size the data is
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}