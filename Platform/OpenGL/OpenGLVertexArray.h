#pragma once

#include <memory>
#include "Engine/src/Renderer/Renderer.h"
#include "Engine/src/Renderer/VertexArray.h"

namespace Engine
{

class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return _vertexBuffers; }
    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return _indexBuffer; }

    static OpenGLVertexArray* Create();

private:
    uint32_t _rendererID;
    std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
    std::shared_ptr<IndexBuffer> _indexBuffer;
}; 

} 
