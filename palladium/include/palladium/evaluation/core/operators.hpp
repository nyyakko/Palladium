#pragma once

#include <string>
#include <unordered_map>
#include <utility>

namespace evaluation
{
    using namespace std::literals;
                                                                        
    static std::unordered_map operators =
    {
        std::pair { "+"sv, + [] (float a, float b) { return a + b; } },
        std::pair { "-"sv, + [] (float a, float b) { return a - b; } },
        std::pair { "*"sv, + [] (float a, float b) { return a * b; } },
        std::pair { "/"sv, + [] (float a, float b) { return a / b; } },
    };
}
