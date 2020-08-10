/*******************************************************************************
** Program name: LivingRoom.cpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This class represents a living room space in the Escape from McFarland game.
**               This class is derived from the Space class. The constructor calls
**               the base class constructor which initializes member variables. The
**               class has a virtual destructor, a takeTurn function which takes the user's
**               choice from the printMenu function and implements a round in the
**               game. printMenu and takeTurn are both pure virtual functions that
**               have different implementations for each derived Space object.
**               printMap is also pure virtual and prints the location of the player
**               for whichever space they are in.
*******************************************************************************/ 
#include "LivingRoom.hpp"
#include "Item.hpp"
#include <string>
#include <iostream>

/*******************************************************************************
*                           LivingRoom::LivingRoom Constructor                 *
* This constructor calls the base class constructor to initialize the          *
* spaceType variable. It then initializes the items vector to include all of   *
* the Item objects in the game. The bool variable hasItem will be set to true  *
* if that item should exist in the LivingRoom space at the start of the game.  *
*******************************************************************************/
LivingRoom::LivingRoom() : Space{LIVING}
{   items = {Item(ROPE, "rope", false), 
             Item(BED_POSTS, "wooden bed posts", false),
             Item(NOODLES, "a packet of ramen noodles", false), 
             Item(POT, "a cooking pot", false),
             Item(WATER_JUG, "a water jug", false),
             Item(COOKBOOK, "a wilderness cookbook", false),
             Item(EGGS, "a pair of eggs", false),
             Item(MAP, "a map of Cook County, Minnesota", true),
             Item(MATCHES, "a box of matches", true),
             Item(MANUAL, "a canoe repair manual", true),
             Item(BOW, "a hunting bow", true),
             Item(ARROWS, "a quiver of arrows", true),
             Item(FISHING_BOOK, "a Minnesota fishing guide", true),
             Item(SAW_DUST, "fine saw dust", false),
             Item(LIFE_JACKET, "a life jacket", false),
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
*                           LivingRoom::~LivingRoom Destructor                 *
* This is a virtual destructor for the LivingRoom class.                       *
*******************************************************************************/
LivingRoom::~LivingRoom()
{
}

/*******************************************************************************
*                           LivingRoom::takeTurn                               *
* This function takes the player's inventory, the number of items in the       *
* inventory, the current turn, the player location, whether the player has     *
* eaten, archery skill, hand-to-hand skill, whether the canoe has been fixed,  *
* the player's sense of direction, the chance to repair a canoe, and fishing   *
* skill as parameters. First, the number of turns remaining is displayed.      *
* Then, printMenu is called displaying the user's options for the current      *
* space. For the living room the user can add items, drop items, or move to    *
* another space. The player can move to the loft or the kitchen from the       *
* living room.                                                                 *
*******************************************************************************/
void LivingRoom::takeTurn(std::vector<Item> &inventory, int &numInventory, int &turn, Space *&playerLoc, 
    bool &hasEaten, int &archerySkill, int &handToHand, bool &canoeFixed, int &senseOfDirection,
    int &repairChance, int &fishingSkill)
{   int choice;     // Stores's the user's menu choice
    static bool readMap = false;    // Signifies whether the player has read the map or not
    static bool readManual = false; // Signifies whether the player has read the manual or not
    static bool readBook = false;   // Signifies whether the player has read the book or not

    std::cout << "You have " << turn << " turns remaining." << std::endl;

    do
    {   choice = playerLoc->printMenu(playerLoc);   // Maybe have to do playerLoc->printMenu();

        switch(choice)
        {   case 1:
            {   playerLoc->addItem(inventory, numInventory);

                // If the player picks up the map, their sense of direction increases
                if(inventory[MAP].hasItem && !readMap)
                {   senseOfDirection += 25 + rand() % 50 + 1;
                    std::cout << "\nYour sense of direction has increased from 25 to " << senseOfDirection
                              << ". You also learn that the road leading\n"
                              << "away from this lake is on the east side of it." << std::endl;
                    readMap = true;
                }

                // If the player picks up the manual, their repair chance increases
                if(inventory[MANUAL].hasItem && !readManual)
                {   repairChance += 25 + rand() % 50 + 1;
                    std::cout << "\nYour chance of repairing a canoe has increased from 25 to "
                              << repairChance << ". You also learn that you would\n"
                              << "need kevlar strips and epoxy resin to repair a canoe." << std::endl;
                    readManual = true;
                }

                // If the player picks up the book, their fishing skill increases
                if(inventory[FISHING_BOOK].hasItem && !readBook)
                {   fishingSkill += 25 + rand() % 50 + 1;
                    std::cout << "\nYour fishing skill has increased from 25 to "
                              << fishingSkill << "." << std::endl;
                    readBook = true;
                }
                break;
            }

            case 2:
            {   playerLoc->dropItem(inventory, numInventory);
                break;
            }

            case 3:
            {   playerLoc = playerLoc->getTop();        // Moves player to the loft
                break;
            }

            case 4:
            {   std::cout << "\nThere is nothing in this direction except the wall of the cabin." << std::endl;
                break;
            }

            case 5:
            {   playerLoc = playerLoc->getLeft();      // Moves player to the kitchen
                break;
            }

            case 6:
            {   std::cout << "\nThere is nothing in this direction except the wall of the cabin." << std::endl;
                break;
            }
        }
    }while(choice != 3 && choice != 5);    // Loop until user selects 3 or 5 to move out of the living room
}

/*******************************************************************************
*                           LivingRoom::printMenu                              *
* This function prints the user's options for different actions to take in the *
* LivingRoom space.                                                            *
*******************************************************************************/
int LivingRoom::printMenu(Space *playerLoc)
{   int choice;     // Holds the user's menu choice

    std::cout << "\nLooking around the living room you see the following items:\n";
    playerLoc->printItems();
    std::cout << "\n\tWhat would you like to do next?\n\n"
              << "1. Pick up an item.\n"
              << "2. Drop an item.\n"
              << "3. Move to the space to the top.\n"
              << "4. Move to the space to the bottom.\n"
              << "5. Move to the space to the left.\n"
              << "6. Move to the space to the right.\n\n"
              << "Please make a selection: ";

    choice = getInteger();

    while(choice < 1 || choice > 6)
    {   std::cout << "The only valid choices are 1-6. Please re-enter: ";
        choice = getInteger();
    }

    return choice;
}

/*******************************************************************************
*                           LivingRoom::printMap                               *
* This function prints the player's location on the map.                       *
*******************************************************************************/
void LivingRoom::printMap(Space *playerLoc)
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
        << "|         |                     |     |o  |     O     |__|  |               |         | \n"
        << "|         |                     |     |   |    -|-    |  |  |               |         | \n"
        << "|         |                     |     |   |    / \\    |__|  |               |         | \n"
        << "|         |                     -----------------------------               |         | \n"
        << "|         |      Shore                 Shore                       Shore    |         | \n"
        << "|         |                                                                 |         | \n"
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
