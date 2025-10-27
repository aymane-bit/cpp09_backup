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

int BitcoinExchange::daysInMonth(int year, int month) // 9
{
    static const int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int daysIn = days[month - 1];

    if (month == 2 && year % 4 == 0)
    {
        if (year % 100 != 0 || year % 400 == 0)
            daysIn = 29;
    }
    return daysIn;
}


bool BitcoinExchange::isValidDate(std::string   date, std::string line)
{
    int year, day, month;

    if (date.size() != 11)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return false;
    }
    if (date[4] != '-' || date[7] != '-')
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return false;
    }
    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] == ' ' && i == date.size() - 1)
            continue;
        if (!std::isdigit(date[i]))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            return false;
        }
    }
    year    = std::atoi(date.substr(0, 4).c_str());
    month   = std::atoi(date.substr(5, 2).c_str());
    day     = std::atoi(date.substr(8, 2).c_str());
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > daysInMonth(year, month))
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return false;
    }
    return true;
}

bool    BitcoinExchange::isInRange(std::string val)
{
    char* end;
    double value = std::strtod(val.c_str(), &end);
    if (value > 1000)
    {
        std::cout << "Error:  too large a number." << std::endl;
        return false;
    }
    if (value < 0)
    {
        std::cout << "Error:  not a positive number." << std::endl;
        return false;
    }
    return true;
}

bool    BitcoinExchange::isValidVal(std::string  val, std::string line)
{
    bool hasDot = false;

    if (val.size() < 2)
    {
        std::cout << "Error:  bad input => " << line << std::endl;
        return false;
    }

    for (size_t i = 0; i < val.size(); ++i)
    {
        char c = val[i];
        if (i == 1 && c == '-')
            continue ;
        if (i == 0)
        {
            if (c == ' ')
                continue;
            std::cout << "Error:  bad input => " << val << std::endl;
            return false;
        }
        if (c == '.')
        {
            if (hasDot)
            {
                std::cout << "Error:  bad input => " << val << std::endl;
                return false;
            }
            hasDot = true;
        }
        else if (!std::isdigit(c))
        {
            std::cout << "Error:  bad input => " << val << std::endl;
            return false;
        }
    }
    if (!isInRange(val.substr(1)))
        return false;
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
            std::cout << "no earlier date found for " << date << std::endl;
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
        size_t      pos = line.find('|');

        if (pos == std::string::npos)
        {
            std::cout << "Error:  bad input => " << line << std::endl;
            continue ;
        }
        std::string date = line.substr(0, pos);
        std::string val  = line.substr(pos + 1);
        if (!isValidDate(date, line))
            continue ;
        if (!isValidVal(val, line))
            continue ;
        double value =  std::atof(val.c_str());
        std::cout << date << " => " << value << " = ";
        fetchValue(date, value);
    }
    file.close();
}
