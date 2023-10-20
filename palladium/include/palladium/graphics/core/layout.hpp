#pragma once

#include <raylib.h>

#include <cstdint>
#include <vector>

namespace ui::layout
{
    enum class Orientation
    {
        HORIZONTAL, VERTICAL
    };

    struct Layout
    {
        Orientation orientation;
        Rectangle container;

        std::vector<Rectangle> items;
    };

    void discard(Rectangle slot);
    Rectangle slot();
    void begin(Orientation orientation, Rectangle slot, std::size_t childrenCount);
    void end();
}
