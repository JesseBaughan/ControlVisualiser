#pragma once

#include <GL/gl3w.h>
#include "shader.h"
#include "vertex_array.h"
#include "index_buffer.h"

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
private:

};