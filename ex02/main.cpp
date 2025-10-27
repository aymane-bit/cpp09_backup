/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:33:58 by aymane            #+#    #+#             */
/*   Updated: 2025/10/18 15:23:41 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: Not enough arguments." << std::endl;
        return 1;
    }

    PmergeMe pmergeMe;

    if (pmergeMe.checkData(argc, argv) == false)
        return 0;
    pmergeMe.sortVector();
    pmergeMe.sortDeque();
    pmergeMe.printInfo();
    return 0;
}