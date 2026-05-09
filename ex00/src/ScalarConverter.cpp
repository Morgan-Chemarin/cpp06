/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:38:53 by dev               #+#    #+#             */
/*   Updated: 2026/05/09 17:42:24 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

static bool isPseudoLiteral(const std::string& str)
{
	if (str == "+inf" || str == "+inff")
	{
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: +inff" << std::endl
				  << "double: +inf" << std::endl;
		return true;
	}
	else if (str == "-inf" || str == "-inff")
	{
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: -inff" << std::endl
				  << "double: -inf" << std::endl;
		return true;
	}
	else if (str == "nan" || str == "nanf")
	{
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: nanf" << std::endl
				  << "double: nan" << std::endl;
		return true;
	}
	return false;
}

static bool isChar(const std::string& str)
{
	if (str.size() == 1 && !isdigit(str[0]))
		return true;
	return false;
}

static bool isInt(const std::string& str)
{
	size_t i = 0;
	
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (i == str.size())
		return false;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

static bool isFloat(const std::string& str)
{
	bool dot = false;
	size_t i = 0;

	if (str.empty() || str[str.size() - 1] != 'f')
		return false;
	if (str[i] == '-' || str[i] == '+')
		i++;
	for (; i < str.size() -1; i++)
	{
		if (str[i] == '.')
		{
            if (dot)
				return false;
            dot = true;
        }
		else if (!isdigit(str[i]))
			return false;
	}
	return dot;
}

static bool isDouble(const std::string& str)
{
    bool dot = false;
    size_t i = 0;

    if (str[i] == '-' || str[i] == '+')
		i++;
    if (i == str.size())
		return false;
    for (; i < str.size(); i++) {
        if (str[i] == '.') {
            if (dot)
				return false;
            dot = true;
        }
		else if (!isdigit(str[i]))
			return false;
    }
    return dot;
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter&)
{
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &str)
{
	char c = 0;
	long int i = 0;
	float f = 0.0f;
	double d = 0.0;

	char* endptr = NULL;

	bool charImpossible = false;
	bool intImpossible = false;

	if (isPseudoLiteral(str))
		return;
	else if (isChar(str))
    {
        c = str[0];
        i = static_cast<int>(c);
        f = static_cast<float>(c);
        d = static_cast<double>(c);
    }
    else if (isInt(str))
    {
        d = std::strtod(str.c_str(), &endptr);
        if (d > INT_MAX || d < INT_MIN)
            intImpossible = true;
        i = static_cast<int>(d);
        f = static_cast<float>(d);
    }
    else if (isFloat(str))
    {
        f = std::strtof(str.c_str(), &endptr);
        d = static_cast<double>(f);
        if (d > INT_MAX || d < INT_MIN)
            intImpossible = true;
        else
            i = static_cast<int>(f);
    }
    else if (isDouble(str))
    {
        d = std::strtod(str.c_str(), &endptr);
		
        f = static_cast<float>(d);
        if (d > INT_MAX || d < INT_MIN)
            intImpossible = true;
        else
            i = static_cast<int>(d);
    }
	else
	{
		std::cout << "Error: Type not found." << std::endl;
        return;
	}

	if (endptr != NULL)
    {
        if (endptr == str.c_str()) {
            std::cout << "Error: Conversion failed" << std::endl;
            return;
        }
        if (*endptr != '\0' && !(*endptr == 'f' && *(endptr + 1) == '\0')) {
            std::cout << "Error: Partial conversion at '" << endptr << "'" << std::endl;
            return;
        }
    }

	if (intImpossible || d < 0 || d > 127)
        charImpossible = true;
    else
	{
		c = static_cast<char>(i);
	}

	std::cout << "char: ";
    if (charImpossible)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(c))
        std::cout << "Non displayable" << std::endl;
    else
	{
		std::cout << "'" << c << "'" << std::endl;
	}
        
	std::cout << "int: ";
    if (intImpossible)
        std::cout << "impossible" << std::endl;
    else
	{
		std::cout << i << std::endl;
	}

	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
    std::cout << "double: " << d << std::endl;
}