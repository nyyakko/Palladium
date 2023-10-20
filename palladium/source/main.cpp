#include "palladium/palladium.hpp"

int main()
{
    static auto constexpr FACTOR = 40;
    static auto constexpr WIDTH  = 9 * FACTOR;
    static auto constexpr HEIGHT = 16 * FACTOR; 

    Palladium palladium {{ WIDTH, HEIGHT }};

    return palladium.run();
}
