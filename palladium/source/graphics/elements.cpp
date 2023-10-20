#include "palladium/graphics/elements.hpp"

#include "palladium/graphics/core/layout.hpp"

#include <raylib.h>
#include <fmt/format.h>

#define DRAW_TEXT(CONTAINER, FONTSIZE, COLOR, CONTENT)                                                                                                                                      \
        do {                                                                                                                                                                                \
            auto const positionX = (CONTAINER.x + (CONTAINER.width / 2)) - static_cast<float>(MeasureText(CONTENT.data(), GetFontDefault().baseSize)) - static_cast<float>(CONTENT.size()); \
            auto const positionY = (CONTAINER.y + (CONTAINER.height / 2)) - static_cast<float>(GetFontDefault().baseSize);                                                                  \
            auto const position  = Vector2 { positionX, positionY };                                                                                                                        \
                                                                                                                                                                                            \
            DrawText(CONTENT.data(), static_cast<std::int32_t>(position.x), static_cast<std::int32_t>(position.y), FONTSIZE, COLOR);                                                        \
        } while (0) 

void ui::element::textbox(Color background, Color foreground, std::int32_t fontSize, std::string_view data)
{
    static constexpr auto BUTTON_SPACING = 5.f;
    
    auto container    = ui::layout::slot();
    container.x      += BUTTON_SPACING / 2;
    container.y      += BUTTON_SPACING / 2;
    container.width  -= BUTTON_SPACING;
    container.height -= BUTTON_SPACING;

    DrawRectangleRounded(container, 0.125f, 2, background);

    DRAW_TEXT(container, fontSize, foreground, data);
}

bool ui::element::button(Color background, Color foreground, std::int32_t fontSize, std::string_view data)
{
    static constexpr auto BUTTON_SPACING = 5.f;

    auto container    = ui::layout::slot();
    container.x      += BUTTON_SPACING / 2;
    container.y      += BUTTON_SPACING / 2;
    container.width  -= BUTTON_SPACING;
    container.height -= BUTTON_SPACING;
    
    if (CheckCollisionPointRec(GetMousePosition(), container))
    {
        DrawRectangleRounded(container, 0.125f, 2, ColorBrightness(background, 0.2f));
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            DrawRectangleRounded(container, 0.125f, 2, ColorBrightness(background, 0.01f));

            return true;
        }
    }
    else
    {
        DrawRectangleRounded(container, 0.125f, 2, background);
    }
    
    DRAW_TEXT(container, fontSize, foreground, data);
    
    return false;
}

void ui::element::pack::button(ui::layout::Orientation orientation, Color background, Color foreground, std::vector<ButtonPack> const& packs)
{
    auto childrenCount = std::accumulate(packs.begin(), packs.end(), 0zu, [](auto total, auto pack)
    {
        return total + pack.names.size();
    }); 
                                                                                                    
    ui::layout::begin(orientation, ui::layout::slot(), childrenCount);
                                                                                                    
    for (auto const& pack : packs)
    {
        std::ranges::for_each(pack.names, [&] (auto&& name)
        {
            if (ui::element::button(background, foreground, FONT_SIZE, name))
            {
                pack.action(name);
            }
        });
                                                                                                    
    }
                                                                                                    
    ui::layout::end();
}
