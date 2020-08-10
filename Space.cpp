/*******************************************************************************
** Program name: Space.cpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This class represents a space in the Escape from McFarland game.
**               It is an abstract class that will act as a node, linking all the
**               derived Space class objects with pointers. Member variables include
**               top, bottom, left, and right which point to other derived Space
**               objects. spaceType keeps track of what kind of derived Space object
**               it is. The struct Item represents an item in the game and the vector
**               items is a list of all the items in a particular space. This class
**               has a default constructor which initializes member variables, a
**               virtual destructor, a takeTurn function which takes the user's
**               choice from the printMenu function and implements a round in the
**               game. printMenu and takeTurn are both pure virtual functions that
**               have different implementations for each derived Space object.
**               printMap is also pure virtual and prints the location of the player
**               for whichever space they are in. There are also get and set functions
**               for member variables. addItem adds an item from the space to the
**               player's inventory. dropItem drops an item from the player's inventory
**               and puts in in the space's 'items' container. printItems prints
**               all the items in a space.
*******************************************************************************/ 
#include "Space.hpp"
#include "Item.hpp"
#include <string>
#include <iostream>

/*******************************************************************************
*                           Space::Space Constructor                           *
* This constructor will be called by derived class constructors to initialize  *
* the member variable, spaceType.                                              *
*******************************************************************************/
Space::Space(SpaceType s) : spaceType {s}
{
}

/*******************************************************************************
*                           Space::~Space Destructor                           *
* This is a virtual destructor for the Space class.                            *
*******************************************************************************/
Space::~Space()
{
}

// Getters
Space * Space::getTop()
{   return top;
}

Space * Space::getBottom()
{   return bottom;
}

Space * Space::getLeft()
{   return left;
}

Space * Space::getRight()
{   return right;
}

Space::SpaceType Space::getSpaceType()
{   return spaceType;
}

// Setters
void Space::setTop(Space *t)
{   top = t;
}

void Space::setBottom(Space *b)
{   bottom = b;
}

void Space::setLeft(Space *l)
{   left = l;
}

void Space::setRight(Space *r)
{   right = r;
}

void Space::setSpaceType(SpaceType s)
{   spaceType = s;
}

/*******************************************************************************
*                           Space::printItems                                  *
* This function displays all the items in a space.                             *
*******************************************************************************/
void Space::printItems()
{   for(unsigned int i = 0; i < items.size(); i++)
    {   if(items[i].hasItem)
        {   std::cout << i << ". " << items[i].sName << std::endl;
        }
    }
}

/*******************************************************************************
*                           Space::addItem                                     *
* This function takes the player's inventory and the number of items in the    *
* inventory as parameters. If the item exists in the space and the player has  *
* room in their inventory, it is removed from the space and added to the       *
* inventory.                                                                   *
*******************************************************************************/
void Space::addItem(std::vector<Item> &inventory, int &numInventory)
{   int itemNum;    // An item's number

    std::cout << "Enter the number of the item: ";
    itemNum = getInteger();
    while(itemNum < 0 || itemNum > 23)
    {   std::cout << "Item numbers go from 0 to 23. Please enter again: ";
        itemNum = getInteger();
    }

    if(items[itemNum].hasItem)
    {   if(numInventory < 8)                    // Maximum inventory is 8 items
        {   items[itemNum].hasItem = false;     // Take item out of the space's items
            inventory[itemNum].hasItem = true;  // Add item to player's inventory
            numInventory++;
        }
        else
        {   std::cout << "\nYour inventory is full. Please drop an item." << std::endl;
        }
    }
    else
    {   std::cout << "\nThere is no item with that number in this space." << std::endl;
    }

    // Display the player's inventory
    std::cout << "\nYour inventory:" << std::endl;
    for(unsigned int i = 0; i < inventory.size(); i++)
    {   if(inventory[i].hasItem)
        {   std::cout << i << ". " << inventory[i].sName << std::endl;
        }
    }
}

/*******************************************************************************
*                           Space::dropItem                                    *
* This function takes the player's inventory as a parameter. First, the        *
* player's inventory is displayed and then the user can choose an item to be   *
* dropped. If the item chosen exists in the player's inventory, it is dropped  *
* from the inventory and added to the items in the space.                      *
*******************************************************************************/
void Space::dropItem(std::vector<Item> &inventory, int &numInventory)
{   int itemNum;    // An item's number

    // Display the player's inventory
    std::cout << "\nYour inventory:" << std::endl;
    for(unsigned int i = 0; i < inventory.size(); i++)
    {   if(inventory[i].hasItem)
        {   std::cout << i << ". " << inventory[i].sName << std::endl;
        }
    }

    // Prompt user for the item to drop
    std::cout << "Enter the number of the item to drop: ";
    itemNum = getInteger();
    while(itemNum < 0 || itemNum > 23)
    {   std::cout << "Item numbers go from 0 to 23. Please enter again: ";
        itemNum = getInteger();
    }

    if(inventory[itemNum].hasItem)
    {   inventory[itemNum].hasItem = false;     // Take item out of the player's inventory
        items[itemNum].hasItem = true;          // Add item to space's items
        numInventory--;
        std::cout << "\n" << items[itemNum].sName << " successfuly dropped." << std::endl;
    }
    else
    {   std::cout << "\nThere is no item with that number in your inventory." << std::endl;
    }
}
