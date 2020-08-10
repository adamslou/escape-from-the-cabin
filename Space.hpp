/*******************************************************************************
** Program name: Space.hpp
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
#ifndef SPACE_HPP
#define SPACE_HPP

#include "getInteger.hpp"
#include "Item.hpp"
#include <string>
#include <vector>

class Space
{   protected:
        Space *top;         // Points to the space to the top of the current one
        Space *bottom;      // Points to the space to the bottom of the current one
        Space *left;        // Points to the space to the left of the current one
        Space *right;       // Points to the space to the right of the current one
        enum SpaceType {LOFT = 1, KITCHEN, LIVING, BOAT, SHORE, TOOL, CAMP, DOCK} spaceType;
        std::vector<Item> items;    // Contains all the items for a Space object

    public:
        Space(SpaceType);    
        virtual ~Space();
        Space * getTop();
        Space * getBottom();
        Space * getLeft();
        Space * getRight();
        SpaceType getSpaceType();
        void setTop(Space *);
        void setBottom(Space *);
        void setLeft(Space *);
        void setRight(Space *);
        void setSpaceType(SpaceType);
        void printItems();
        void addItem(std::vector<Item> &, int &);
        void dropItem(std::vector<Item> &, int &);
        virtual void takeTurn(std::vector<Item> &, int &, int &, Space *&, bool &, int &, int &,
                              bool &, int &, int &, int &) = 0;
        virtual int printMenu(Space *) = 0;
        virtual void printMap(Space *) = 0;
};
#endif
