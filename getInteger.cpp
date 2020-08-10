/*******************************************************************************
** Program name: getInteger.cpp
** Author:       Louis Adams
** Date:         2019-04-21     		             	
** Description:  This is the getInteger function implementation file.
** Adapted from: https://www.learncpp.com/cpp-tutorial/5-10-stdcin-extraction-and-
**               dealing-with-invalid-text-input/
*******************************************************************************/ 
#include "getInteger.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

int getInteger()
{   int num;
    std::string input;
    bool inputValid = false;

    // Loop until valid input is entered
    while(!inputValid)
    {   getline(std::cin, input);
        inputValid = true;

        // If any character in the line is not a digit, it is invalid
        for(unsigned int i = 0; i < input.length(); i++)
        {   if(!isdigit(input[i]))
            {   inputValid = false;
            }
        }

        if(!inputValid)
        {   std::cout << "Input is invalid. Please enter a valid input: ";
        }
        else
        {   std::stringstream sStream;
            sStream << input;
            sStream >> num;

            // Check to see if an int fails to be extracted from the stringstream,
            // such as would be the case if the number is higher than 2147483647,
            // the maximum size of an int.
            if(sStream.fail())
            {   sStream.clear();
                sStream.ignore(32767, '\n');
                inputValid = false;
                std::cout << "Input is invalid. Please enter a valid input: ";
            }
        }
    }
    return num;
}
