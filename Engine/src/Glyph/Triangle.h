#pragma once

#include <memory>

#include "Glyph.h"
#include "Renderer/Renderer.h"

namespace Engine
{
    class TriangleGlyph : public Glyph
    {
    public:
        TriangleGlyph();
        ~TriangleGlyph() {};

        virtual void Draw(Window* window) override;
        virtual void Insert(Glyph* glyph, int id) override;
        virtual void Remove(Glyph* glyph) override;

    private:
        float vehicle_vertices[9] = {
            -0.1f, -0.3f, 0.0f, //0
            0.1f, -0.3f, 0.0f,  //1
            0.0f,  0.3f, 0.0f   //2
        };

        unsigned int indices[3] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
        };  

        VertexArray _va;
        //VertexBufferLayout _layout;
        std::unique_ptr<Shader> _shader;
        std::unique_ptr<VertexBuffer> _vb;
        std::unique_ptr<IndexBuffer> _ib;
        Renderer _renderer;
    };

}