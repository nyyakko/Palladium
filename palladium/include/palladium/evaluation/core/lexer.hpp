#pragma once

#include "evaluation/core/token.hpp"

#include <sstream>
#include <vector>
#include <string_view>

namespace evaluation
{
    struct Lexer
    {
    public:
        explicit Lexer(std::string_view expression): expressionStream(expression.data()) {}
        Lexer(Lexer const& lexer): expressionStream(lexer.expressionStream.str()) {}
    
    public:
        bool has_next_token();
        Token next_token();
        std::vector<Token> tokenize();
    
    public:
        Lexer operator=(Lexer const&);

    private:
        std::stringstream expressionStream;
    
        bool is_eof();
        bool is_number(std::string_view);
        bool is_operator(std::string_view);
        bool is_function(std::string_view);
    };
}
