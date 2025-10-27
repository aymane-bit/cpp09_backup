/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:32:28 by aymane            #+#    #+#             */
/*   Updated: 2025/10/18 15:21:45 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// C.O.F

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    this->numbersVector = other.numbersVector;
    this->numbersDeque = other.numbersDeque;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        this->numbersVector = other.numbersVector;
        this->numbersDeque = other.numbersDeque;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

// mm fct

void        PmergeMe::printInfo(void) const
{
    std::cout << "After:  ";
    for (size_t i = 0; i < numbersVector.size(); i++)
        std::cout << numbersVector[i] << " ";
    std::cout << "\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time to process a range of " << numbersVector.size() 
    << " elements with std::[vector] : " << (timeVector * 1e6) << " us" << std::endl;

    std::cout << "Time to process a range of " << numbersDeque.size() 
              << " elements with std::[deque]  : " 
              << (timeDeque * 1e6) << " us" << std::endl;
}

bool        PmergeMe::isNotDigite(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (i == 0 && (str[i] == '+' || str[i] == '-'))
        {
            if (str.size() == 1)
                return false;
            continue;        
        }
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}

void    PmergeMe::copyData(const std::vector<int>     listNumber)
{
    for (size_t i = 0; i < listNumber.size(); i++)
        numbersVector.push_back(listNumber[i]);    

    for (size_t i = 0; i < listNumber.size(); i++)
        numbersDeque.push_back(listNumber[i]);

    std::cout << "Before: ";
    for (size_t i = 0; i < numbersDeque.size(); i++)
        std::cout << numbersDeque[i] << " ";
    std::cout << std::endl;
}

bool        PmergeMe::checkForDup(const std::vector<int>& temp)
{
    for (size_t i = 0; i < temp.size(); ++i)
        for (size_t j = i + 1; j < temp.size(); ++j)
            if (temp[i] == temp[j])
                return true;
    return false;
}

bool        PmergeMe::checkData(int argc, char **argv) 
{
    std::vector<int>  temp;
    
    for (int i = 1; i < argc; i++)
    {
        if (isNotDigite(argv[i]) == false)
        {
            std::cout << "Error : Invalid Input\n";
            return false;            
        }
        int number = std::atoi(argv[i]);
        if (number < 0)
        {
            std::cout << "Error : Negative Number\n";
            return false;
        }
        temp.push_back(number);
    }
    if (checkForDup(temp))
    {
        std::cout << "Error : Duplicate Number Found!\n";
        return false;
    }
    copyData(temp);
    return true;
}

void    PmergeMe::sortVector( void )
{
    std::vector<int>    small;
    std::vector<int>    large;

    clock_t start = clock(); //  3 4  1 2   small == 3 2 large 1 2
    for (size_t i = 0; i + 1 < numbersVector.size(); i += 2)
    {
        if (numbersVector[i] > numbersVector[i + 1])
            std::swap(numbersVector[i], numbersVector[i + 1]);
    }
    for (size_t i = 0; i + 1 < numbersVector.size(); i += 2)
    {
        small.push_back(numbersVector[i]);
        large.push_back(numbersVector[i + 1]);
    }
    if (numbersVector.size() % 2 != 0)
        small.push_back(numbersVector.back());

    for (size_t i = 1; i < small.size(); ++i) // 3 2 1 cur = 2 pos = 1 knt hna <<<<<<<<<<<<<<<<<<<<<<
    {
        int current = small[i];          // Take the current element
        size_t position = i;             // Start comparing from its position
    
        // Shift larger elements to the right
        while (position > 0 && small[position - 1] > current)
        {
            small[position] = small[position - 1];
            --position;
        }
    
        // Insert the element at its correct place
        small[position] = current;
    }

    for (size_t i = 0; i < large.size(); ++i)
    {
        int val = large[i];
        size_t pos = 0;
    
        // find position to insert
        while (pos < small.size() && small[pos] < val)
            ++pos;
    
        // insert at pos
        small.insert(small.begin() + pos, val); // works with deque as well
    }
    numbersVector = small;
    timeVector = double(clock() - start) / CLOCKS_PER_SEC;
}


void    PmergeMe::sortDeque( void )
{
    std::deque<int>    small;
    std::deque<int>    large;

    clock_t start = clock();
    for (size_t i = 0; i + 1 < numbersDeque.size(); i += 2)
    {
        if (numbersDeque[i] > numbersDeque[i + 1])
            std::swap(numbersDeque[i], numbersDeque[i + 1]);
    }
    for (size_t i = 0; i + 1 < numbersDeque.size(); i += 2)
    {
        small.push_back(numbersDeque[i]);
        large.push_back(numbersDeque[i + 1]);
    }
    if (numbersDeque.size() % 2 != 0)
        small.push_back(numbersDeque.back());
    for (size_t i = 1; i < small.size(); ++i)
    {
        int current = small[i];          // Take the current element
        size_t position = i;             // Start comparing from its position
    
        // Shift larger elements to the right
        while (position > 0 && small[position - 1] > current)
        {
            small[position] = small[position - 1];
            --position;
        }
    
        // Insert the element at its correct place
        small[position] = current;
    }
    for (size_t i = 0; i < large.size(); ++i)
    {
        int val = large[i];
        size_t pos = 0;
    
        // find position to insert
        while (pos < small.size() && small[pos] < val)
            ++pos;
    
        // insert at pos
        small.insert(small.begin() + pos, val); // works with deque as well
    }
    numbersDeque = small;
    timeDeque = double(clock() - start) / CLOCKS_PER_SEC;   
}