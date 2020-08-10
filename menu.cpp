/*******************************************************************************
** Program name: menu.cpp
** Author:       Louis Adams
** Date:         2019-04-23     		             	
** Description:  This is the menu function implementation file.
*******************************************************************************/ 
#include "menu.hpp"
#include "getInteger.hpp"
#include <iostream>

int menu()
{   int choice;     // Holds the user's menu choice

    std::cout << "\n\tWelcome to Escape from McFarland!\n\n"
              << "1. Play game.\n"
              << "2. Exit game.\n\n"
              << "Please make a selection: ";

    choice = getInteger();

    while(choice < 1 || choice > 2)
    {   std::cout << "The only valid choices are 1-2. Please re-enter: ";
        choice = getInteger();
    }

    return choice;
}
