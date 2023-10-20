#include "palladium/evaluation/evaluation.hpp"

#include "palladium/evaluation/core/operators.hpp"

#include <stack>
#include <sstream>

float evaluation::evaluate(std::vector<Token> const& expression)
{
    std::stack<float> resultStack {};

    for (auto const& token : expression)
    {
        if (token.type == TokenType::NUMBER)
        {
            float value {};
            std::stringstream { token.value } >> value;

            resultStack.push(value);
        }
        
        if (token.type == TokenType::OPERATOR)
        {
            auto rhs = resultStack.top();
            resultStack.pop();
            auto lhs = resultStack.top();
            resultStack.pop();

            resultStack.push(operators[token.value](lhs, rhs));
        }
    }

    return resultStack.top();
}
