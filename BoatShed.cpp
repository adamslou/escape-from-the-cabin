/*******************************************************************************
** Program name: BoatShed.cpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This class represents a boat shed space in the Escape from McFarland game.
**               This class is derived from the Space class. The constructor calls
**               the base class constructor which initializes member variables. The
**               class has a virtual destructor, a takeTurn function which takes the user's
**               choice from the printMenu function and implements a round in the
**               game. printMenu and takeTurn are both pure virtual functions that
**               have different implementations for each derived Space object.
**               printMap is also pure virtual and prints the location of the player
**               for whichever space they are in.
*******************************************************************************/ 
#include "BoatShed.hpp"
#include "Item.hpp"
#include <string>
#include <iostream>

/*******************************************************************************
*                           BoatShed::BoatShed Constructor                     *
* This constructor calls the base class constructor to initialize the          *
* spaceType variable. It then initializes the items vector to include all of   *
* the Item objects in the game. The bool variable hasItem will be set to true  *
* if that item should exist in the BoatShed space at the start of the game.    *
*******************************************************************************/
BoatShed::BoatShed() : Space {BOAT}
{   items = {Item(ROPE, "rope", false), 
             Item(BED_POSTS, "wooden bed posts", false),
             Item(NOODLES, "a packet of ramen noodles", false), 
             Item(POT, "a cooking pot", false),
             Item(WATER_JUG, "a water jug", false),
             Item(COOKBOOK, "a wilderness cookbook", false),
             Item(EGGS, "a pair of eggs", false),
             Item(MAP, "a map of Cook County, Minnesota", false),
             Item(MATCHES, "a box of matches", false),
             Item(MANUAL, "a canoe repair manual", false),
             Item(BOW, "a hunting bow", false),
             Item(ARROWS, "a quiver of arrows", false),
             Item(FISHING_BOOK, "a Minnesota fishing guide", false),
             Item(SAW_DUST, "fine saw dust", true),
             Item(LIFE_JACKET, "a life jacket", true),
             Item(STICKS, "some small sticks", false),
             Item(KEVLAR_STRIPS, "kevlar strips", false),
             Item(EPOXY, "some epoxy resin", false),
             Item(FISHING_POLE, "a fishing pole", false),
             Item(CHOPPED_LOGS, "chopped firewood", false),
             Item(AXE, "an axe", false),
             Item(TARGET, "a shooting target", false),
             Item(BOARDS, "wooden boards", false),
             Item(FISH, "a live walleye", false)};
}

/*******************************************************************************
*                           BoatShed::~BoatShed Destructor                     *
* This is a virtual destructor for the BoatShed class.                         *
*******************************************************************************/
BoatShed::~BoatShed()
{
}

/*******************************************************************************
*                           BoatShed::takeTurn                                 *
* This function takes the player's inventory, the number of items in the       *
* inventory, the current turn, the player location, whether the player has     *
* eaten, archery skill, hand-to-hand skill, whether the canoe has been fixed,  *
* the player's sense of direction, the chance to repair a canoe, and fishing   *
* skill as parameters. First, the number of turns remaining is displayed.      *
* Then, printMenu is called displaying the user's options for the current      *
* space. For the boat shed the user can add items, drop items, or move to      *
* another space. The player can move to shore 1 from the boat shed. The player *
* can also repair a cracked canoe if they have the right inventory items       *
*******************************************************************************/
void BoatShed::takeTurn(std::vector<Item> &inventory, int &numInventory, int &turn, Space *&playerLoc, 
    bool &hasEaten, int &archerySkill, int &handToHand, bool &canoeFixed, int &senseOfDirection,
    int &repairChance, int &fishingSkill)
{   int choice;     // Stores the user's menu choice

    std::cout << "You have " << turn << " turns remaining." << std::endl;

    do
    {   choice = playerLoc->printMenu(playerLoc);   // Maybe have to do playerLoc->printMenu();

        switch(choice)
        {   case 1:
            {   playerLoc->addItem(inventory, numInventory);
                break;
            }

            case 2:
            {   playerLoc->dropItem(inventory, numInventory);
                break;
            }

            case 3:
            {   std::cout << "\nThere is nothing in this direction except the wall of the shed." << std::endl;
                break;
            }

            case 4:
            {   std::cout << "\nThere is nothing in this direction except the wall of the shed." << std::endl;
                break;
            }

            case 5:
            {   std::cout << "\nThere is nothing in this direction except the wall of the shed." << std::endl;
                break;
            }

            case 6:
            {   playerLoc = playerLoc->getRight();      // Moves player to shore 1
                break;
            }

            case 7:
            {   // Player attempts to repair the canoe in the boat shed
                if(!canoeFixed)
                {   if(inventory[KEVLAR_STRIPS].hasItem && inventory[EPOXY].hasItem)
                    {   int repairRoll = rand() % 100 + 1;  // Represents the player's chance to fix the canoe.
                        if(repairRoll <= repairChance)
                        {   std::cout << "\nYour attempt has succeeded. However the repair took 5 minutes of\n"
                                      << "crucial time. As you turn the canoe over you even see a paddle\n"
                                      << "wedged in under the seat. You will now be able to launch this boat\n"
                                      << "from the dock." << std::endl;
                            canoeFixed = true;
                            inventory[KEVLAR_STRIPS].hasItem = false;
                            inventory[EPOXY].hasItem = false;
                            numInventory -= 2;
                            turn -= 5;
                        }
                        else
                        {   std::cout << "\nYour attempt has failed. In addition, you spent 5 minutes trying\n"
                                      << "to repair the canoe." << std::endl;
                            turn -= 5;
                        }
                    }
                    else
                    {   std::cout << "\nYou spend 3 minutes milling around before you realize you don't have\n"
                                  << "the proper materials for the job." << std::endl;
                        turn -= 3;
                    }
                }
                else
                {   std::cout << "\nYou must not be thinking or seeing clearly. The canoe is already fixed."
                              << std::endl;
                }
            }
        }
    }while(choice != 6);    // Loop until user selects 6 to move out of the boat shed
}

/*******************************************************************************
*                           BoatShed::printMenu                                *
* This function prints the user's options for different actions to take in the *
* BoatShed space.                                                              *
*******************************************************************************/
int BoatShed::printMenu(Space *playerLoc)
{   int choice;     // Holds the user's menu choice

    std::cout << "\nLooking around the boat shed you see the following items:\n";
    playerLoc->printItems();
    std::cout << "There is also a kevlar canoe with a severe crack in the bottom hull.\n"
              << "You can see the boat wouldn't make it far with the crack left as is." << std::endl;
    std::cout << "\n\tWhat would you like to do next?\n\n"
              << "1. Pick up an item.\n"
              << "2. Drop an item.\n"
              << "3. Move to the space to the top.\n"
              << "4. Move to the space to the bottom.\n"
              << "5. Move to the space to the left.\n"
              << "6. Move to the space to the right.\n"
              << "7. Attempt to repair the canoe.\n\n"
              << "Please make a selection: ";

    choice = getInteger();

    while(choice < 1 || choice > 7)
    {   std::cout << "The only valid choices are 1-7. Please re-enter: ";
        choice = getInteger();
    }

    return choice;
}

/*******************************************************************************
*                           BoatShed::printMap                                 *
* This function prints the player's location on the map.                       *
*******************************************************************************/
void BoatShed::printMap(Space *playerLoc)
{
    std::cout << '\n';
    std::cout 
        << "   ^   ^                ^                         ^                                 ^   \n"
        << "  /|\\ /|\\              /|\\           ^           / \\                               /|\\  \n"
        << "  /|\\ /|\\              /|\\          /|\\         /   \\             ^                /|\\  \n"
        << "  /|\\ /|\\              /|\\     ^    /|\\        /Loft \\           /|\\     ^         /|\\  \n"
        << "   |   |      Campfire  |     /|\\   /|\\       /       \\          /|\\    /|\\         |    \n"
        << "                 ooo          /|\\    |       /         \\         /|\\    /|\\             \n"
        << "          ^     o ^ o         /|\\           /         |_\\         |     /|\\             \n"
        << "         /|\\    o^^^o          |           /          |  \\               |              \n"
        << "     ^   /|\\    o ^ o             /-----------------------\\                      ^      \n"
        << "    / \\  /|\\     ooo             / Kitchen|  Living Room | \\          ^         / \\     \n"
        << "   /   \\  |                     /         |           |__|  \\        /|\\       /   \\    \n"
        << "  /     \\                       |         |           |  |  |        /|\\      /     \\   \n"
        << " / Boat  \\                      |     ----|           |__|  |        /|\\     / Tool  \\  \n"
        << "/  Shed   \\                     |     |   |           |  |  |         |     /  Shed   \\ \n"
        << "|         |                     |     |o  |           |__|  |               |         | \n"
        << "|         |                     |     |   |           |  |  |               |         | \n"
        << "|         |                     |     |   |           |__|  |               |         | \n"
        << "|    O    |                     -----------------------------               |         | \n"
        << "|   -|-   |      Shore                 Shore                       Shore    |         | \n"
        << "|   / \\   |                                                                 |         | \n"
        << "-----------                                                                 ----------- \n"
        << "                                                                                        \n"
        << ",,,,,,,,,,,,,,,,,,       ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
        << "           ~     |       |        ~                         ~         ~            ~    \n"
        << "~    ~           |       |    ~         ~        ~     ~        ~             ~      ~  \n"
        << "  ~           ~  |       |      ~     ~        McFarland Lake         ~           ~     \n"
        << "        ~        | Dock  |  ~              ~          ~         ~           ~          ~\n"
        << " ~           ~   |       |         ~               ~                 ~            ~     \n"
        << "      ~          |       |    ~              ~             ~              ~          ~  \n"
        << "  ~           ~  |       |        ~               ~                ~               ~    \n"
        << "     ~      ~    |       |     ~             ~           ~                  ~          ~\n"
        << "          ~      ---------            ~            ~                    ~               \n"
        << "   ~                       ~                   ~                                 ~      \n"
        << std::endl;
}
