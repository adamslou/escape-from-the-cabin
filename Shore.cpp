/*******************************************************************************
** Program name: Shore.cpp
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
#include "Shore.hpp"
#include "Item.hpp"
#include <string>
#include <iostream>

/*******************************************************************************
*                           Shore::Shore Constructor                           *
* This constructor calls the base class constructor to initialize the          *
* spaceType variable. It then initializes the items vector to include all of   *
* the Item objects in the game. The bool variable hasItem will be set to true  *
* if that item should exist in the Shore space at the start of the game.       *
*******************************************************************************/
Shore::Shore() : Space {SHORE}
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
             Item(SAW_DUST, "fine saw dust", false),
             Item(LIFE_JACKET, "a life jacket", false),
             Item(STICKS, "some small sticks", true),
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
*                           Shore::~Shore Destructor                           *
* This is a virtual destructor for the Shore class.                            *
*******************************************************************************/
Shore::~Shore()
{
}

/*******************************************************************************
*                           Shore::takeTurn                                    *
* This function takes the player's inventory, the number of items in the       *
* inventory, the current turn, the player location, whether the player has     *
* eaten, archery skill, hand-to-hand skill, whether the canoe has been fixed,  *
* the player's sense of direction, the chance to repair a canoe, and fishing   *
* skill as parameters. First, the number of turns remaining is displayed.      *
* Then, printMenu is called displaying the user's options for the current      *
* space. For the shore the user can add items, drop items, or move to          *
* another space. From shore 1 the player can move to the campfire, shore 2,    *
* the dock, or the boat shed. From shore 2 the player can move to the kitchen, *
* shore 1, or shore 3. From shore 3 the player can move to shore 2 or the tool *
* shed.                                                                        *
*******************************************************************************/
void Shore::takeTurn(std::vector<Item> &inventory, int &numInventory, int &turn, Space *&playerLoc, 
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
            {   if(playerLoc->getTop())
                {   playerLoc = playerLoc->getTop();      // Moves player to the campfire or the kitchen
                }
                else
                {   std::cout << "\nThere is nothing in this direction except impenetrable forest.\n" 
                              << "You try entering but quickly realize it is hopeless. You've lost\n"
                              << "3 precious minutes in your attempt." << std::endl;
                    turn -= 2;      // Subtract 2 additional turns besides the standard one
                }
                break;
            }

            case 4:
            {   if(playerLoc->getBottom())
                {   playerLoc = playerLoc->getBottom(); // Moves player to the dock
                }
                else
                {   std::cout << "\nThere is nothing in this direction except the lake which must\n" 
                              << "be at least a kilometer across. You try swimming but quickly realize\n"
                              << "it is hopeless. There is a brisk wind moving against you and you are\n"
                              << "not a good swimmer. You've lost 3 precious minutes in your attempt." 
                              << std::endl;
                    turn -= 2;      // Subtract 2 additional turns besides the standard one
                }
                break;
            }

            case 5:
            {   playerLoc = playerLoc->getLeft();// Moves player to the space to the left
                break;
            }

            case 6:
            {   playerLoc = playerLoc->getRight();// Moves player to the space to the right
                break;
            }
        }
    }while(choice != 3 && choice != 4 && choice !=5 && choice !=6);    // Loop until user selects 3, 4, 5, 
                                                                       // or 6 to move out of the kitchen
}

/*******************************************************************************
*                           Shore::printMenu                                   *
* This function prints the user's options for different actions to take in the *
* Shore space.                                                                 *
*******************************************************************************/
int Shore::printMenu(Space *playerLoc)
{   int choice;     // Holds the user's menu choice

    std::cout << "\nLooking around the shore you see the following items:\n";
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
*                           Shore::printMap                                    *
* This function prints the player's location on the map.                       *
*******************************************************************************/
void Shore::printMap(Space *playerLoc)
{   if(playerLoc->getTop() && playerLoc->getTop()->getSpaceType() == CAMP)
    {   // print a map with the player in shore 1
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
        << "|         |                     -----------------------------               |         | \n"
        << "|         |      Shore                 Shore                       Shore    |         | \n"
        << "|         |       O                                                         |         | \n"
        << "-----------      -|-                                                        ----------- \n"
        << "                 / \\                                                                    \n"
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
    else if(playerLoc->getTop() && playerLoc->getTop()->getSpaceType() == KITCHEN)
    {   // print a map with the player in shore 2
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
        << "|         |                     -----------------------------               |         | \n"
        << "|         |      Shore                 Shore                       Shore    |         | \n"
        << "|         |                             O                                   |         | \n"
        << "-----------                            -|-                                  ----------- \n"
        << "                                       / \\                                              \n"
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
    else
    {   // print a map with the player in shore 3
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
        << "|         |                     -----------------------------               |         | \n"
        << "|         |      Shore                 Shore                       Shore    |         | \n"
        << "|         |                                                       O         |         | \n"
        << "-----------                                                      -|-        ----------- \n"
        << "                                                                 / \\                    \n"
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
}
