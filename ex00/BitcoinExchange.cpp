/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 23:31:01 by aymane            #+#    #+#             */
/*   Updated: 2025/10/17 10:12:08 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"


// C.O.F
BitcoinExchange::BitcoinExchange()
{
    // std::cout << "bitcoinExchange constructor is called\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& original)
{
    std::cout << "bitcoinExchange copy constructor is called\n";
    this->data = original.data;
}

BitcoinExchange::~BitcoinExchange()
{
    // std::cout << "bitcoinExchange destructor is called\n";
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& original)
{
    std::cout << "bitcoinExchange assignment operator is called\n";
    if (this != &original)
        this->data = original.data;
    return (*this);
}

// mm functions

bool BitcoinExchange::isValidDate(std::string   date)
{
    int year, day, month;

    if (date.size() != 11)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] == ' ' && i == date.size() - 1)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    year    = std::atoi(date.substr(0, 4).c_str());
    month   = std::atoi(date.substr(5, 2).c_str());
    day     = std::atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    if (year < 1)
        return false;
    return true;
}

bool    BitcoinExchange::isvalidVal(double  val)
{
    if (val < 0 || val > 1000)
    {
        if (val < 0)
            std::cout << "Error: not a positive number." << std::endl;
        else
            std::cout << "Error: too large a number." << std::endl;
        return false;   
    }
    return true;
}

void BitcoinExchange::loadData(void)
{
    std::ifstream file("data.csv");
    std::string   line;

    if (!file.is_open())
    {
        std::cout << "Error : could not open file.\n";
        return ;
    }
    std::getline(file, line);
    while(std::getline(file, line))
    {
        std::string date;
        double      value;
        
        std::istringstream iss(line);
        std::getline(iss, date, ',');
        iss >> value;
        data[date] = value;
    }
    file.close();
}

void    BitcoinExchange::fetchValue(std::string date, double val)
{
    if (data.empty())
        return;

    std::map<std::string,double>::iterator it = data.lower_bound(date);

    if (it == data.end() || it->first > date)
    {
        if (it == data.begin())
        {
            std::cout << "Error: no earlier date found for " << date << std::endl;
            return;
        }
        --it;
    }

    std::cout << val * it->second << std::endl;
}

void BitcoinExchange::openData(const char *fileName)
{
    std::ifstream file(fileName);
    std::string   line;

    if (!file.is_open())
    {
        std::cout << "Error : could not open file.\n";
        return ;
    }
    std::getline(file, line);
    while(std::getline(file, line))
    {
        double      value;
        size_t pos = line.find('|');
        if (pos != std::string::npos)
        {
            std::string date = line.substr(0, pos);
            std::string val  = line.substr(pos + 1);
            value =  std::atof(val.c_str());
            if (isValidDate(date) == true && isvalidVal(value) == true)
            {
                std::cout << date << " => " << val << " = ";
                fetchValue(date, value);
            }
        }
        else
            std::cout << "Error: bad input => " << line << std::endl;
    }
    file.close();
}
