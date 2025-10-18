/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:46:21 by aymane            #+#    #+#             */
/*   Updated: 2025/10/18 06:30:20 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::~RPN()
{
}

RPN::RPN()
{
}

RPN::RPN(const RPN& original)
{
    *this = original;
}

RPN& RPN::operator=(const RPN& original)
{
    if (this != &original)
        this->operands = original.operands;
    return (*this);
}

bool    RPN::isValidFormat(const std::string& expression) const 
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1)
        {
            char c = token[0];
            if (std::isdigit(c) || isOperator(c))
                continue;
        }
        std::cout << "Error : Invalid charachter\n";
        return false;
    }
    return true;
}

void    RPN::evaluate(std::string expression)
{
    if (isValidFormat(expression) == false)
        return ;

    bool performedOperation = false;
    for (size_t i = 0; i < expression.size(); ++i)
    {
        if (expression[i] == ' ')
            continue;
        if (std::isdigit(expression[i]))
        {
            int num = expression[i] - '0';
            operands.push(num);
        }
        else
        {
            if (operands.size() < 2)
            {
                std::cout << "Error: not enough operands\n";
                return ;
            }
            int b = operands.top();operands.pop();
            int a = operands.top();operands.pop();
            switch (expression[i])
            {
                case '+': operands.push(a + b); break;
                case '-': operands.push(a - b); break;
                case '*': operands.push(a * b); break;
                case '/': 
                if (b == 0)
                {
                    std::cout << "Error: division by zero\n";
                    return;
                }
                operands.push(a / b);
                break;
                default:
                    std::cout << "Error: Unknown operator!" << std::endl;
                    return;
            }
            performedOperation = true;
        }
    }
    if (operands.size() != 1 || !performedOperation)
    {
        std::cout << "Error: invalid expression (stack not empty at end)\n";
        return ;
    }
    std::cout << operands.top() << std::endl;
}
 
bool    RPN::isOperator(char c) const 
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
