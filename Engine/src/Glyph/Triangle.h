#pragma once

#include "Glyph.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"

namespace Engine
{
    class TriangleGlyph : public Glyph
    {
    public:
        TriangleGlyph();
        ~TriangleGlyph();

        virtual void Draw(Window* window) override;
        virtual void Insert(Glyph* glyph, int id) override;
        virtual void Remove(Glyph* glyph) override;

    private:
    /*
           Shader *_shader;
           Renderer *_renderer;
           VertexArray *_va;
           VertexBuffer *_vb;
           VertexBufferLayout *_layout;
           IndexBuffer *_ib;
           */
    };

}