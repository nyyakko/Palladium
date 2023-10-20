#include "palladium/evaluation/parser.hpp"

#include <algorithm>
#include <ranges>
#include <stack>

using namespace evaluation;

std::vector<Token> Parser::parse()
{
    std::stack<Token> operatorsStack {};
    
    for (auto const& token : this->lexer.tokenize())
    {
        if (this->is_number(token))
        {
            expression.push_back(token);
            continue;
        }
        
        if (this->is_function(token))
        {
            operatorsStack.push(token);
            continue;
        }
        
        while (!operatorsStack.empty())
        {
            auto hasLowerPrecedence = token.precedence < operatorsStack.top().precedence;
            auto hasEqualPrecedence = token.precedence == operatorsStack.top().precedence;
                                                                                                    
            if (this->is_parenthesis(operatorsStack.top()) && operatorsStack.top().value == "(")
            {
                break;
            }
            
            if (!(hasLowerPrecedence || (hasEqualPrecedence && token.fixity == TokenFixity::LEFT)))
            {
                break;
            }
            
            auto lastOperator = operatorsStack.top();
            operatorsStack.pop();
            
            this->expression.push_back(lastOperator);
        }
        
        operatorsStack.push(token);
    }
    
    std::ranges::for_each(std::views::iota(0zu, operatorsStack.size()), [&] (auto)
    {
        expression.push_back(operatorsStack.top());
        operatorsStack.pop();
    });
    
    return this->expression;
}

bool Parser::is_number(Token const& token)
{
    return token.type == TokenType::NUMBER;
}

bool Parser::is_operator(Token const& token)
{
    return token.type == TokenType::OPERATOR;
}

bool Parser::is_function(Token const& token)
{
    return token.type == TokenType::FUNCTION;
}

bool Parser::is_parenthesis(Token const& token)
{
    return token.type == TokenType::PARENTHESIS;
}
