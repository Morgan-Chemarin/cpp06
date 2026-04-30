/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:38:53 by dev               #+#    #+#             */
/*   Updated: 2026/04/30 17:53:02 by dev              ###   ########.fr       */
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
		return 1;
	}
	else if (str == "-inf" || str == "-inff")
	{
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: -inff" << std::endl
				  << "double: -inf" << std::endl;
		return 1;
	}
	else if (str == "nan" || str == "nanf")
	{
		std::cout << "char: impossible" << std::endl
				  << "int: impossible" << std::endl
				  << "float: nanf" << std::endl
				  << "double: nan" << std::endl;
		return 1;
	}
	return 0;
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &str)
{
	if (isPseudoLiteral(str))
		return;

	double d = 0.0;
    char* endptr = NULL;

	if (str.length() == 1 && !std::isdigit(str[0]))
        d = static_cast<double>(str[0]);
	else {
        d = std::strtod(str.c_str(), &endptr);
        if (endptr == str.c_str()) {
            std::cout << "char: impossible" << std::endl
					  << "int: impossible" << std::endl
					  << "float: impossible" << std::endl
					  << "double: impossible" << std::endl;
            return;
        }
        if (*endptr != '\0' && !(*endptr == 'f' && *(endptr + 1) == '\0')) {
            std::cout << "char: impossible" << std::endl
					  << "int: impossible" << std::endl
					  << "float: impossible" << std::endl
					  << "double: impossible" << std::endl;
            return;
        }
    }
	
	std::cout << "char: ";
    if (d < 0 || d > 127 || std::isnan(d)) 
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(d)))
        std::cout << "Non displayable" << std::endl;
    else
	{
        std::cout << "'" << static_cast<char>(d) << "'" << std::endl;
	}

	std::cout << "int: ";
    if (d < INT_MIN || d > INT_MAX || std::isnan(d))
        std::cout << "impossible" << std::endl;
    else
	{
        std::cout << static_cast<int>(d) << std::endl;
	}
	std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: ";
	
	if (std::isinf(static_cast<float>(d)) && !std::isinf(d))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<float>(d) << "f" << std::endl;

	std::cout << "double: ";
	if (std::isinf(d))
		std::cout << (d > 0 ? "+inf" : "-inf") << std::endl;
	else
		std::cout << d << std::endl;
}