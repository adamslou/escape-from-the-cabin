/*******************************************************************************
** Program name: Item.hpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This struct represents an inventory item. Member variables include
**               an enum type Name which represents the name of the inventory item.
**               sName is the name of the item represented as a string. hasItem
**               is a bool that represents whether the item is included or not in
**               a certain space's inventory or the player character's inventory.
**               A constructor is provided which takes 3 parameters and uses them
**               to initialize all 3 member variables.
*******************************************************************************/ 
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "Name.hpp"

struct Item
{   Name name;
    std::string sName;      // The name of an inventory item as a string
    bool hasItem;

    // Constructor
    Item(Name n, std::string s, bool h) : name {n}, sName {s}, hasItem {h}
    {
    }
};
#endif
