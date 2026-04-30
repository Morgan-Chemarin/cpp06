/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 18:04:30 by dev               #+#    #+#             */
/*   Updated: 2026/04/30 18:14:32 by dev              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    Data myData;
    myData.id = 42;
    myData.name = "Bob";

    Data* ptrOriginal = &myData;
    uintptr_t raw = Serializer::serialize(ptrOriginal);
    Data* ptrConverted = Serializer::deserialize(raw);

    std::cout << "Original pointer : " << ptrOriginal << std::endl;
    std::cout << "Raw value : " << raw << std::endl;
    std::cout << "Converted pointer : " << ptrConverted << std::endl;

    if (ptrConverted == ptrOriginal) {
        std::cout << "Success: The pointers are identical" << std::endl;
        std::cout << "Data : " << ptrConverted->name << " " << ptrConverted->id << std::endl;
    } else {
        std::cout << "Error: The pointers differ" << std::endl;
    }

    return 0;
}