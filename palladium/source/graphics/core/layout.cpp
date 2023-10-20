#include "palladium/graphics/core/layout.hpp"

#include <cassert>
#include <stack>
#include <cmath>

static inline auto& layout_stack()
{
    static std::stack<ui::layout::Layout> stack {};
    return stack;
}

void ui::layout::discard(Rectangle slot)
{
    (void)slot;
}

Rectangle ui::layout::slot()
{
    auto& stack = layout_stack();

    if (!(stack.top().items.size() < stack.top().items.capacity()))
    {
        // std::clog << std::stacktrace::current();
        assert(false && "LAYOUT STACK OVERFLOW");
    }
     
    auto const& root          = stack.top();
    auto const& rootContainer = root.container;
    auto const  rootCapacity  = static_cast<float>(root.items.capacity());
    auto const  rootSize      = static_cast<float>(root.items.size());

    Rectangle rectangle {};

    switch (root.orientation)
    {
        case Orientation::HORIZONTAL:
            rectangle.width  = ceilf(rootContainer.width / rootCapacity);
            rectangle.height = rootContainer.height;
            rectangle.x      = rootContainer.x + ceilf((rootContainer.width / rootCapacity) * rootSize);
            rectangle.y      = rootContainer.y;
            
            break;
        
        case Orientation::VERTICAL:
            rectangle.width  = rootContainer.width;
            rectangle.height = ceilf(rootContainer.height / rootCapacity);
            rectangle.x      = rootContainer.x;
            rectangle.y      = rootContainer.y + ceilf((rootContainer.height / rootCapacity) * rootSize);
            
            break;
    }
    
    stack.top().items.push_back(rectangle);
    
    return rectangle;
}

void ui::layout::begin(Orientation orientation, Rectangle container, std::size_t childrenCount)
{
    Layout layout
    {
        .orientation = orientation,
        .container = container,
        .items = {}
    };
    
    layout.items.reserve(childrenCount);
    
    layout_stack().push(std::move(layout));
}

void ui::layout::end()
{
    layout_stack().pop();
}
