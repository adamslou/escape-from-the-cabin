/*******************************************************************************
** Program name: Game.hpp
** Author:       Louis Adams
** Date:         2019-06-02     		             	
** Description:  The Game class represents the Escape from the Cabin game. The
**               player must move around different spaces and perform certain tasks
**               in order to escape. The spaces are objects derived from the Space
**               class. playerLoc points to the space occupied by the player.
**               The player has an inventory made up of Item structs. There are also
**               various attributes, skills, and states for the player represented
**               by the variables fatigued, hasEaten, archerySkill, handToHand,
**               canoeFixed, senseOfDirection, repairChance, and fishingSkill.
**               There are pointers to each of the derived Space objects that will
**               be used to dynamically allocate and deallocate memory.
**               Member functions include a default constructor, a destructor,
**               and several get and set functions. The start function sets up the
**               story and provides background. It then gets the user's choice by 
**               calling the startMenu function. At the end of the start function
**               the play funciton is called to start the turn-based gameplay.
**               There is a special event that occurs with 20 turns remaining. At
**               this moment in the game, the returnEarlyEvent function is called.
**               Once the number of turns reaches 0 or the player escapes the game
**               is over.
*******************************************************************************/
#ifndef GAME_HPP
#define GAME_HPP

#include "Space.hpp"
#include "Item.hpp"
#include <vector>

class Game
{   private:
        Space *playerLoc;                   // Points to the player's location
        std::vector<Item> inventory;        // Represents the player's inventory
        int numInventory;                   // Represents the number of items in the player's inventory
        bool fatigued;                      // Represents whether the player is fatigued
        bool hasEaten;                      // Represents whether the player has eaten
        int archerySkill;                   // Represents the player's archery skill
        int handToHand;                     // Represents the player's hand to hand combat skill
        bool canoeFixed;                    // Represents whether the canoe has been fixed or not
        int senseOfDirection;               // Represents the player's sense of direction
        int repairChance;                   // Represents the player's chance to repair the canoe
        int fishingSkill;                   // Represents the player's fishing skill
        Space *loft;
        Space *kitchen;
        Space *livingRoom;
        Space *boatShed;                    // These point to various spaces
        Space *shore1;
        Space *shore2;
        Space *shore3;
        Space *toolShed;
        Space *campfire;
        Space *dock;
        
    public:
        Game();
        ~Game();
        Space * getPlayerLoc();
        bool getFatigued();
        void setPlayerLoc(Space *);
        void setFatigued(bool);
        void start();
        int startMenu();
        void play(int);
        void returnEarlyEvent(int &);
};
#endif
