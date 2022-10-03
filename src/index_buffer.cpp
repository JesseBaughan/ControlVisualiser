#include "index_buffer.h"

#include "renderer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    //Bind our vertex buffer array to GL_ARRAY_BUFFER - this is now active
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); 
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}