/*******************************************************************************
** Program name: main.cpp
** Author:       Louis Adams
** Date:         2019-06-06     		             	
** Description:  This program allows the user to play the Escape from the Cabin game.
**               The main function will call the menu function to display the
**               starting menu and get a choice from the user. If the user chooses
**               to start the game, a Game object will be instantiated and the
**               Game class's start function will be called. Once the game is over
**               the user will have the option to play again as many times as
**               she/he wishes. The rand() function is also seeded before the 
**               menu function is called.
*******************************************************************************/ 
#include "Game.hpp"
#include "menu.hpp"
#include <cstdlib>
#include <ctime>

int main()
{   unsigned int seed = time(nullptr);
    srand(seed);
    int choice;             // Stores the user's menu choice

    do
    {   choice = menu();

        switch(choice)
        {   case 1:
            {   Game game;
                game.start();
                break;
            }

            case 2: break;
        }
    }while(choice != 2);    // Loop until user selects 2 to quit

    return 0;
}
