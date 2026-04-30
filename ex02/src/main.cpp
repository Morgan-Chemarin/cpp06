/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:18:03 by mchemari          #+#    #+#             */
/*   Updated: 2026/04/30 22:05:52 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <iostream> 
#include <time.h>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate(void)
{
    int random = rand() % 3;
    if (random == 0)
    {
        std::cout << "Instance A has been created." << std::endl;
        return new A();
    }
        
    else if (random == 1)
    {
        std::cout << "Instance B has been created." << std::endl;
        return new B();
    }
    else
    {
        std::cout << "Instance C has been created." << std::endl;
        return new C();
    }
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "Pointer found A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "Pointer found B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "Pointer found C" << std::endl;
    else
        std::cout << "No pointer found" << std::endl;
}

void identify(Base &p)
{
    try
    {
        A test = dynamic_cast<A&>(p);
        std::cout << "Reference A found" << std::endl;
    }
    catch(const std::exception& e) {}
    try
    {
        B test = dynamic_cast<B&>(p);
        std::cout << "Reference B found" << std::endl;
    }
    catch(const std::exception& e) {}
    try
    {
        C test = dynamic_cast<C&>(p);
        std::cout << "Reference C found" << std::endl;
    }
    catch(const std::exception& e) {}
}

int main()
{
    srand(time(NULL));
    
    for (int i = 0; i < 5; i++)
    {
        std::cout << "\n--- Test" << i + 1 << " ---" << std::endl;
        
        Base* obj = generate();
        identify(obj);
        identify(*obj);

        delete obj;
    }
    return 0;
}