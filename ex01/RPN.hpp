/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:17:04 by aymane            #+#    #+#             */
/*   Updated: 2025/10/17 12:14:14 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>

#include <stack>
#include <sstream>
#include <stdexcept>


class   RPN
{
    private:
        std::stack<int> operands;
        
    public :
    // C.O.F
        ~RPN();
        RPN();
        RPN(const RPN& original);
        RPN& operator=(const RPN& original);
    // mm fct
        void    evaluate(std::string expression);
        bool    isOperator(char c) const ;
        bool    isValidFormat(const std::string& expression) const ;
    

};




#endif