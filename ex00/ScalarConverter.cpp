/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:38:53 by dev               #+#    #+#             */
/*   Updated: 2026/04/19 16:35:05 by dev              ###   ########.fr       */
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

static bool isChar(const std::string& str)
{
	if (str.size() == 1 && !isdigit(str[0])) // "4" '4' '"4"' true or false ?
		return true;
	return false;
}

static bool isInt(const std::string& str)
{
	int i = 0;
	
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
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
	int i = 0;
	int nbDot = 0;
	int nbF = 0;

	//* 42.f  / 42.0f
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return false;
	while (str[i])
	{
		if (isdigit(str[i]) || str[i] == '.' || str[i] == 'f')
		{
			if (str[i] == 'f')
				nbF++;
			if (str[i] == '.')
				nbDot++;
		}
		else
			return false;
		i++;
	}
	if (str[str.size() - 1] == 'f' && nbDot == 1 && nbF == 1)
		return true;
	return false;
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
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

	bool charImpossible = false;
	bool intImpossible = false;

	//! cas spéciaux
	if (isPseudoLiteral(str))
	{
		return;
	}
	//! detection type of parameter
	else if (isChar(str))
	{
		c = str[0];
		i = static_cast<int>(c);
		f = static_cast<float>(c);
		d = static_cast<double>(c);
	}
	else if (isInt(str))
	{
		char* endptr;
		i = std::strtol(str.c_str(), &endptr, 10);
		c = static_cast<char>(i);
		f = static_cast<float>(i);
		d = static_cast<double>(i);

		if (i > INT_MAX || i < INT_MIN)
			intImpossible = true;
		if (endptr == str.c_str())
		{
			std::cout << "conversion echoué" << std::endl; // refacto error
			return ;
		}
		else if (*endptr != '\0')
		{
			std::cout << "conversion partiel" << endptr << std::endl; // refacto error
			return ;
		}
		if (i < 0 || i > 127 || intImpossible)
			charImpossible = true;
	}
	else if (isFloat(str))
	{
		char* endptr;
		f = std::strtof(str.c_str(), &endptr);
		if (f > static_cast<float>(INT_MAX) || f < static_cast<float>(INT_MIN))
			intImpossible = true;
		else
			i = static_cast<int>(f);
		c = static_cast<char>(f);
		d = static_cast<double>(f);

		if (endptr == str.c_str())
		{
			std::cout << "conversion echoué" << std::endl; // refacto error
			return ;
		}
		else if (*endptr != '\0' && (*endptr != 'f' || *(endptr + 1) != '\0'))
		{
			std::cout << "conversion partiel" << endptr << std::endl; // refacto error
			return ;
		}
		if (i < 0 || i > 127 || intImpossible)
			charImpossible = true;
	}
	else
	{
		std::cout << "Type not found." << std::endl;
		return ;
	}

	//! AFFICHAGE

	// char
	if (charImpossible)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(c))	
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << c << "'" << std::endl;

	// int
	if (intImpossible)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << i << std::endl;

	// float / double
	std::cout << std::fixed << std::setprecision(1)
			  << "float: " << f << "f" << std::endl
			  << "double: " << d << std::endl;
	return ;
}

// else if (isDouble(str))
// {
// 	const char *s = str.c_str();
// 	char* endptr;
// 	double d = std::strtod(s, &endptr);

// 	if (endptr == s)
// 		std::cout << "conversion echoué" << std::endl;
// 	else if (*endptr != '\0')
// 		std::cout << "conversion partiel" << endptr << std::endl;
// }