#pragma once

#include "evaluation/lexer.hpp"

#include <vector>

namespace evaluation
{
    struct Parser
    {
    public:
        explicit Parser(Lexer const& lexer): lexer(lexer) {}
    
    public:
        std::vector<Token> expression;
    
        std::vector<Token> parse();
    
    private:
        Lexer lexer;
    
        bool is_number(Token const& token);
        bool is_operator(Token const& token);
        bool is_function(Token const& token);
        bool is_parenthesis(Token const& token);
    };
}
