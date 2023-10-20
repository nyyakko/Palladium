#include "palladium/evaluation/core/lexer.hpp"

#include "palladium/evaluation/core/operators.hpp"

#include <algorithm>
#include <cassert>

using namespace evaluation;

bool Lexer::has_next_token()
{
    return !this->is_eof();
}

Token Lexer::next_token()
{
    assert(!this->is_eof() && "TRIED TO TOKENIZE EMPTY STREAM");
                                                                 
    Token result {};
    
    this->expressionStream >> result.value;
    
    if (this->is_number(result.value))
    {
        result.type = TokenType::NUMBER;
        result.precedence = TokenPrecedence::NONE;
                                                                 
        return result;
    }
                                                                 
    if (this->is_function(result.value))
    {
        result.type = TokenType::FUNCTION;
        result.precedence = TokenPrecedence::NONE;
                                                                 
        return result;
    }
                                                                 
    if (this->is_operator(result.value))
    {
        if (result.value == "+" || result.value == "-")
        {
            result.type = TokenType::OPERATOR;
            result.fixity = TokenFixity::RIGHT;
            result.precedence = TokenPrecedence::TERTIARY;
                                                                 
            return result;
        }
                                                                 
        if (result.value == "*" || result.value == "/")
        {
            result.type = TokenType::OPERATOR;
            result.fixity = TokenFixity::LEFT;
            result.precedence = TokenPrecedence::SECONDARY;
                                                                 
            return result;
        }
                                                                 
        if (result.value == "(" || result.value == ")")
        {
            result.type = TokenType::PARENTHESIS;
            result.precedence = TokenPrecedence::PRIMARY;
                                                                 
            return result;
        }
    }
    
    assert(false && "UNRECOGNIZED TOKEN DETECTED");

    return {};
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens {};
                                              
    while (!this->is_eof())
    {
        tokens.push_back(this->next_token());
    }
                                              
    return tokens;
}

Lexer Lexer::operator=(Lexer const& lhs)
{
    if (lhs.expressionStream.str().empty())
    {
        return *this;
    }

    return lhs; 
}

bool Lexer::is_eof()
{
    return this->expressionStream.eof();
}

bool Lexer::is_number(std::string_view value)
{
    return std::ranges::any_of(value, ::isdigit);
}

bool Lexer::is_operator(std::string_view value)
{
    return evaluation::operators.contains(value);
}

bool Lexer::is_function(std::string_view value)
{
    return value == "SIN"  || value == "COS" || value == "TAN" || value == "SQRT" || value == "LOG" || value == "POW";
}
