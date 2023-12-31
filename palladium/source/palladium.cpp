#include "palladium/palladium.hpp"

#include "palladium/color.hpp"
#include "palladium/evaluation/core/lexer.hpp"
#include "palladium/evaluation/core/parser.hpp"
#include "palladium/evaluation/evaluation.hpp"
#include "palladium/graphics/core/layout.hpp"
#include "palladium/graphics/elements.hpp"

#include <raylib.h>
#include <fmt/format.h>

#include <cassert>

Palladium::Palladium(std::pair<std::int32_t, std::int32_t> resolution): resolution(resolution)
{
    auto const& [width, height] = this->resolution;
                                                    
    InitWindow(width, height, "Palladium");
}

std::int32_t Palladium::run()
{
    SetTargetFPS(24);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            this->update();
            this->render();
        }
        EndDrawing();
    }

    return 69;
}

void Palladium::update()
{
    if (IsKeyPressed(KEY_LEFT_SHIFT) && !this->shift_mode)
    {
        this->shift_mode = true;
    }
    else if (IsKeyPressed(KEY_LEFT_SHIFT) && this->shift_mode)
    {
        this->shift_mode = false;
    }
}

void Palladium::render()
{
    using namespace ui;

    ClearBackground(color::CHARCOAL_BLACK);

    auto const resolutionWidth  = static_cast<float>(this->resolution.first);
    auto const resolutionHeight = static_cast<float>(this->resolution.second);

    Rectangle const mainFrame = { 0, 0, resolutionWidth, resolutionHeight };

    ui::layout::begin(ui::layout::Orientation::VERTICAL, mainFrame, 6);
    {
        ui::element::textbox(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, this->expression);
        
        ui::layout::begin(ui::layout::Orientation::HORIZONTAL, ui::layout::slot(), 4);
        {
            if (!this->shift_mode)
            {
                if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "PUSH"))
                {
                    this->expressionHistory.push_back(this->expression);
                }

                if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "POP"))
                {
                    if (!this->expression.empty())
                    {
                        this->expression = this->expressionHistory.back();
                        this->expressionHistory.pop_back();
                    }
                }

                if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "CLEAR"))
                {
                    this->expression = "";
                }
            }
            else
            {
                if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "SIN"))
                    assert(false && "NOT IMPLEMENTED");

                if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "COS"))
                    assert(false && "NOT IMPLEMENTED");

                if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "TAN"))
                    assert(false && "NOT IMPLEMENTED");
            }

            if (ui::element::button(color::OBSIDIAN_BLACK, color::RAY_WHITE, FONT_SIZE, "="))
            {
                evaluation::Lexer expressionLexer { this->expression };
                evaluation::Parser expressionParser { expressionLexer };

                this->expression = std::to_string(evaluation::evaluate(expressionParser.parse()));
            }

        }
        ui::layout::end(); 

        using namespace ui::layout;
        using namespace ui::element::pack;

        auto fnAppend = [this] (auto value) { this->expression.append(value); };

        element::pack::button(Orientation::HORIZONTAL, color::OBSIDIAN_BLACK, color::RAY_WHITE, {{ fnAppend, { "1", "2", "3", " * " }}});
        element::pack::button(Orientation::HORIZONTAL, color::OBSIDIAN_BLACK, color::RAY_WHITE, {{ fnAppend, { "4", "5", "6", " / " }}});
        element::pack::button(Orientation::HORIZONTAL, color::OBSIDIAN_BLACK, color::RAY_WHITE, {{ fnAppend, { "7", "8", "9", " + " }}});
        element::pack::button(Orientation::HORIZONTAL, color::OBSIDIAN_BLACK, color::RAY_WHITE, {{ fnAppend, { "(", "0", ")", " - " }}});
    }
    ui::layout::end();
}
