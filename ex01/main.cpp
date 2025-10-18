/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:44:34 by aymane            #+#    #+#             */
/*   Updated: 2025/10/18 06:44:04 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **argv)
{

    if (ac != 2)
    {
        std::cerr << "Error: invalid number of arguments." << std::endl;
        return 1;
    }
    RPN rpn;
    rpn.evaluate(argv[1]);

    return 0;
}