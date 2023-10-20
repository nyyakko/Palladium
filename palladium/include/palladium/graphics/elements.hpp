#pragma once

#include "palladium.hpp"

#include "graphics/core/layout.hpp"

#include "raylib.h"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <numeric>
#include <string_view>

namespace ui::element
{
    void textbox(Color background, Color foreground, std::int32_t fontSize, std::string_view data);
    bool button(Color background, Color foreground, std::int32_t fontSize, std::string_view data);
}

namespace ui::element::pack
{
    struct ButtonPack
    {
        std::function<void(std::string_view)> action {};
        std::vector<std::string_view> names {};
    };

    void button(ui::layout::Orientation orientation, Color background, Color foreground, std::vector<ButtonPack> const& packs);
}
