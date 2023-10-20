#pragma once

#include <string>

namespace evaluation
{
    enum class TokenType
    {
        NUMBER, OPERATOR, FUNCTION, PARENTHESIS
    };
    
    enum class TokenPrecedence
    {
        NONE, TERTIARY, SECONDARY, PRIMARY
    };
    
    enum class TokenFixity
    {
        LEFT, RIGHT
    };
    
    struct Token
    {
        TokenType type;
        TokenPrecedence precedence;
        TokenFixity fixity;
    
        std::string value;
    };
}
