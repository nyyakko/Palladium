#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <utility>

static constexpr auto FONT_SIZE = 20;

class Palladium
{
public:
    explicit Palladium(std::pair<std::int32_t, std::int32_t> resolution);

public:
    std::int32_t run();

    void update();
    void render();

private:
    std::pair<std::int32_t, std::int32_t> resolution {};

    std::string expression {};
    std::vector<std::string> expressionHistory {};

    bool shift_mode = false;
};
