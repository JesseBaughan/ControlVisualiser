#pragma once

#include "vertex_buffer.h"

class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const; 
    void UnBind() const; 

private:
    unsigned int m_RendererID;
};