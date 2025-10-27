/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 06:49:09 by aymane            #+#    #+#             */
/*   Updated: 2025/10/18 15:19:41 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>



class PmergeMe
{
    private :
        std::vector<int>    numbersVector;
        std::deque<int>     numbersDeque;
        double              timeVector;
        double              timeDeque;
    public :
        // C.O.F
            PmergeMe();
            PmergeMe(const PmergeMe &other);
            PmergeMe &operator=(const PmergeMe &other);
            ~PmergeMe();
            // mm fct
            bool    checkData(int argc, char **argv);
            bool    isNotDigite(std::string str);
            bool    checkForDup(const std::vector<int>& temp);
            void    copyData(const std::vector<int>     listNumber);
            void    sortVector(void);
            void    sortDeque (void);
            void    printInfo(void) const ;
};





#endif