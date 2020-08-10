/*******************************************************************************
** Program name: Shore.hpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This class represents a shore space in the Escape from McFarland game.
**               This class is derived from the Space class. The constructor calls
**               the base class constructor which initializes member variables. The
**               class has a virtual destructor, a takeTurn function which takes the user's
**               choice from the printMenu function and implements a round in the
**               game. printMenu and takeTurn are both pure virtual functions that
**               have different implementations for each derived Space object.
**               printMap is also pure virtual and prints the location of the player
**               for whichever space they are in.
*******************************************************************************/ 
#ifndef SHORE_HPP
#define SHORE_HPP

#include "Space.hpp"
#include "Item.hpp"
#include <vector>

class Shore : public Space
{   private:

    public:
        Shore();
        virtual ~Shore();
        virtual void takeTurn(std::vector<Item> &, int &, int &, Space *&, bool &, int &, int &,
                              bool &, int &, int &, int &);
        virtual int printMenu(Space *);
        virtual void printMap(Space *);
};
#endif
