//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_CONSOLE_H
#define HEADHUNTER_CONSOLE_H

#include <iostream>

#include "debug.h"

#define INFO(args) std::cout << args << std::endl;

#define WARN(args) std::cerr << "WARNING: " << args << std::endl;

#define ERROR(args) std::cerr << "ERROR: " << args << std::endl; throw std::exception();

#ifdef HEADHUNTER_DEBUG
    #define DEBUG(args) std::cout << args << std::endl;
#else
    #define DEBUG(args) ;
#endif

#endif //HEADHUNTER_CONSOLE_H
