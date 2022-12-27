#pragma once

#include "Window.h"

namespace Engine
{
    class Glyph
    {
    public:
        Glyph() {};
        virtual ~Glyph() {};

        virtual void Draw(Window* window) = 0;
        //virtual void Bounds(Rect& rect);
        //virtual void Intersects(const Point& point);
        virtual void Insert(Glyph* glyph, int id) = 0;
        virtual void Remove(Glyph* glyph) = 0;
    private:
        //virtual Glyph* Child(int id);
        //virtual Glyph* Parent();
    };
}