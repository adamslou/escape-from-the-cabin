/*******************************************************************************
** Program name: Dock.cpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This class represents a dock space in the Escape from McFarland game.
**               This class is derived from the Space class. The constructor calls
**               the base class constructor which initializes member variables. The
**               class has a virtual destructor, a takeTurn function which takes the user's
**               choice from the printMenu function and implements a round in the
**               game. printMenu and takeTurn are both pure virtual functions that
**               have different implementations for each derived Space object.
**               printMap is also pure virtual and prints the location of the player
**               for whichever space they are in.
*******************************************************************************/ 
#include "Dock.hpp"
#include "Item.hpp"
#include <string>
#include <iostream>

/*******************************************************************************
*                           Dock::Dock Constructor                             *
* This constructor calls the base class constructor to initialize the          *
* spaceType variable. It then initializes the items vector to include all of   *
* the Item objects in the game. The bool variable hasItem will be set to true  *
* if that item should exist in the Dock space at the start of the game.        *
*******************************************************************************/
Dock::Dock() : Space {DOCK}
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
*                           Dock::~Dock Destructor                             *
* This is a virtual destructor for the Dock class.                             *
*******************************************************************************/
Dock::~Dock()
{
}

/*******************************************************************************
*                           Dock::takeTurn                                     *
* This function takes the player's inventory, the number of items in the       *
* inventory, the current turn, the player location, whether the player has     *
* eaten, archery skill, hand-to-hand skill, whether the canoe has been fixed,  *
* the player's sense of direction, the chance to repair a canoe, and fishing   *
* skill as parameters. First, the number of turns remaining is displayed.      *
* Then, printMenu is called displaying the user's options for the current      *
* space. For the dock the user can add items, drop items, or move to           *
* another space. The player can move to shore 1 from the dock. The player      *
* can also go fishing or launch a boat from the dock if they have the right    *
* inventory items to do so.                                                    *
*******************************************************************************/
void Dock::takeTurn(std::vector<Item> &inventory, int &numInventory, int &turn, Space *&playerLoc, 
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
            {   playerLoc = playerLoc->getTop();        // Moves player to shore 1
                break;
            }

            case 4:
            {   std::cout << "\nThere is nothing in this direction except the lake which must\n" 
                          << "be at least a kilometer across. You try swimming but quickly realize\n"
                          << "it is hopeless. There is a brisk wind moving against you and you are\n"
                          << "not a good swimmer. You've lost 3 precious minutes in your attempt." 
                          << std::endl;
                turn -= 3;
                break;
            }

            case 5:
            {   std::cout << "\nThere is nothing in this direction except the lake which must\n" 
                          << "be at least a kilometer across. You try swimming but quickly realize\n"
                          << "it is hopeless. There is a brisk wind moving against you and you are\n"
                          << "not a good swimmer. You've lost 3 precious minutes in your attempt." 
                          << std::endl;
                turn -= 3;
                break;
            }

            case 6:
            {   std::cout << "\nThere is nothing in this direction except the lake which must\n" 
                          << "be at least a kilometer across. You try swimming but quickly realize\n"
                          << "it is hopeless. There is a brisk wind moving against you and you are\n"
                          << "not a good swimmer. You've lost 3 precious minutes in your attempt." 
                          << std::endl;
                turn -= 3;
                break;
            }

            case 7:
            {   if(inventory[FISHING_POLE].hasItem)
                {   int fishingRoll = rand() % 100 + 1;
                    if(fishingRoll <= fishingSkill)
                    {   int cast = rand() % 3 + 1;
                        std::cout << "\nYou've caught a nice walleye on cast #" << cast << "! However,\n"
                                  << "you doubt you can stomach eating a raw fish. You'll need to cook\n"
                                  << "it if you hope to get any benefit. If only you could make a fire\n"
                                  << "somewhere..." << std::endl;
                        inventory[FISH].hasItem = true;
                        numInventory++;
                    }
                    else
                    {   std::cout << "\nYou fail to catch any fish." << std::endl;
                    }
                    std::cout << "You spent 1 minute in your attempt." << std::endl;
                }
                else
                {   std::cout << "\nYou don't have a fishing pole." << std::endl;
                }
                break;
            }

            case 8:
            {   // Player attempts to launch a boat
                if(hasEaten)
                {   if(canoeFixed)
                    {   std::cout << "\nYou successfully launch the canoe from the boat shed. You sit in the\n"
                                  << "stern of the boat and paddle into McFarland lake. You just hope your\n"
                                  << "sense of direction is good enough to get you to the nearest road so\n"
                                  << "that you can escape your captors and this wilderness. Based on the\n"
                                  << "contour of the McFarland shoreline and the position of the sun in the\n"
                                  << "sky you take your best guess and paddle away in that direction." 
                                  << std::endl;
                        int directionRoll = rand() % 100 + 1;
                        if(directionRoll <= senseOfDirection)
                        {   std::cout << "\nIt seems your sense of direction must be sound as you soon see a\n"
                                      << "boat landing leading to a road. You get out of the canoe and start\n"
                                      << "jogging down the road. Not long after you are rescued by a\n"
                                      << "patrolling forest ranger." << std::endl;
                            turn += 110;
                        }
                        else
                        {   std::cout << "\nYour sense of direction has lead you astray. After a few minutes\n"
                                      << "you hear your captors boat coming. You know you can't outrun their.\n"
                                      << "motorboat." << std::endl;
                            turn -= 50;
                        }
                    }
                    else
                    {   std::cout << "\nThere is no boat capable of being launched that won't sink within\n"
                                  << "minutes." << std::endl;
                        turn++; // Account for loss of turn by selecting this option
                    }
                }
                else
                {   std::cout << "\nYou have no hope of traversing McFarland lake and escaping the northern\n"
                              << "Minnesota wilderness if you don't get something to eat." << std::endl;
                    turn++;     // Account for loss of turn by selecting this option
                }
            }
        }
    }while(choice != 3 && choice != 8);    // Loop until user selects 3 or 8 to move off the dock
}

/*******************************************************************************
*                           Dock::printMenu                                    *
* This function prints the user's options for different actions to take in the *
* Dock space.                                                                  *
*******************************************************************************/
int Dock::printMenu(Space *playerLoc)
{   int choice;     // Holds the user's menu choice

    std::cout << "\nLooking around the dock you see the following items:\n";
    playerLoc->printItems();
    std::cout << "\n\tWhat would you like to do next?\n\n"
              << "1. Pick up an item.\n"
              << "2. Drop an item.\n"
              << "3. Move to the space to the top.\n"
              << "4. Move to the space to the bottom.\n"
              << "5. Move to the space to the left.\n"
              << "6. Move to the space to the right.\n"
              << "7. Go fishing.\n"
              << "8. Launch a boat.\n\n"
              << "Please make a selection: ";

    choice = getInteger();

    while(choice < 1 || choice > 8)
    {   std::cout << "The only valid choices are 1-8. Please re-enter: ";
        choice = getInteger();
    }

    return choice;
}

/*******************************************************************************
*                           Dock::printMap                                     *
* This function prints the player's location on the map.                       *
*******************************************************************************/
void Dock::printMap(Space *playerLoc)
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
        << " ~           ~   |   O   |         ~               ~                 ~            ~     \n"
        << "      ~          |  -|-  |    ~              ~             ~              ~          ~  \n"
        << "  ~           ~  |  / \\  |        ~               ~                ~               ~    \n"
        << "     ~      ~    |       |     ~             ~           ~                  ~          ~\n"
        << "          ~      ---------            ~            ~                    ~               \n"
        << "   ~                       ~                   ~                                 ~      \n"
        << std::endl;
}
