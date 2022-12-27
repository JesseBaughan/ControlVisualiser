#pragma once

#include "src/Window.h"

namespace Engine
{
    class Glyph
    {
    public:
        virtual void Draw(Window* window);
        virtual void Bounds(Rect& rect);
        virtual void Intersects(const Point& point);
        virtual void Insert(Glyph* glyph, int id);
        virtual void Remove(Glyph* glyph)
    private:
        virtual Glyph* Child(int id);
        virtual Glyph* Parent();
    }
}