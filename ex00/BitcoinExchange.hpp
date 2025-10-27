/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:54:22 by aymane            #+#    #+#             */
/*   Updated: 2025/10/17 10:18:02 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>


class BitcoinExchange
{
    private :
        std::map<std::string, double> data;
    public :
    // C.O.F
        ~BitcoinExchange();
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& original);
        BitcoinExchange& operator=(const BitcoinExchange& original);
    // Methods
        void    loadData   (void);
        void    openData   (const char* fileName);
        bool    isValidDate(std::string     date, std::string line);
        bool    isValidVal (std::string           val, std::string line);
        void    fetchValue (std::string date, double val);
        int     daysInMonth(int year, int month);
        bool    isInRange(std::string val);
};





#endif