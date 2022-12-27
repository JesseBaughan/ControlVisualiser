#pragma once

#include "Glyph.h"

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
    };

}