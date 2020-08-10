/*******************************************************************************
** Program name: Campfire.cpp
** Author:       Louis Adams
** Date:         2019-06-03     		             	
** Description:  This class represents a campfire space in the Escape from McFarland game.
**               This class is derived from the Space class. The constructor calls
**               the base class constructor which initializes member variables. The
**               class has a virtual destructor, a takeTurn function which takes the user's
**               choice from the printMenu function and implements a round in the
**               game. printMenu and takeTurn are both pure virtual functions that
**               have different implementations for each derived Space object.
**               printMap is also pure virtual and prints the location of the player
**               for whichever space they are in.
*******************************************************************************/ 
#include "Campfire.hpp"
#include "Item.hpp"
#include <string>
#include <iostream>

/*******************************************************************************
*                           Campfire::Campfire Constructor                     *
* This constructor calls the base class constructor to initialize the          *
* spaceType variable. It then initializes the items vector to include all of   *
* the Item objects in the game. The bool variable hasItem will be set to true  *
* if that item should exist in the Campfire space at the start of the game.    *
*******************************************************************************/
Campfire::Campfire() : Space {CAMP}
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
*                           Campfire::~Campfire Destructor                     *
* This is a virtual destructor for the Campfire class.                         *
*******************************************************************************/
Campfire::~Campfire()
{
}

/*******************************************************************************
*                           Campfire::takeTurn                                 *
* This function takes the player's inventory, the number of items in the       *
* inventory, the current turn, the player location, whether the player has     *
* eaten, archery skill, hand-to-hand skill, whether the canoe has been fixed,  *
* the player's sense of direction, the chance to repair a canoe, and fishing   *
* skill as parameters. First, the number of turns remaining is displayed.      *
* Then, printMenu is called displaying the user's options for the current      *
* space. For the campfire the user can add items, drop items, or move to       *
* another space. The player can move to shore 1 from the campfire. The player  *
* can also make a fire, cook something, practice archery, or practice          *
* hand-to-hand combat in this space if they have the right inventory items to  *
* do so.                                                                       *
*******************************************************************************/
void Campfire::takeTurn(std::vector<Item> &inventory, int &numInventory, int &turn, Space *&playerLoc, 
    bool &hasEaten, int &archerySkill, int &handToHand, bool &canoeFixed, int &senseOfDirection,
    int &repairChance, int &fishingSkill)
{   int choice;                     // Stores the user's menu choice
    static bool madeFire = false;   // Represents whether the player has made a fire or not

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
            {   std::cout << "\nThere is nothing in this direction except impenetrable forest.\n" 
                          << "You try entering but quickly realize it is hopeless. You've lost\n"
                          << "3 precious minutes in your attempt." << std::endl;
                turn -= 3;
                break;
            }

            case 4:
            {   playerLoc = playerLoc->getBottom();      // Moves player to shore 1
                break;
            }

            case 5:
            {   std::cout << "\nThere is nothing in this direction except impenetrable forest.\n" 
                          << "You try entering but quickly realize it is hopeless. You've lost\n"
                          << "3 precious minutes in your attempt." << std::endl;
                turn -= 3;
                break;
            }

            case 6:
            {   std::cout << "\nThere is nothing in this direction except the wall of the cabin." << std::endl;
                break;
            }

            case 7:
            {   // The player makes a fire if they have materials for making a fire
                if(inventory[MATCHES].hasItem && (inventory[SAW_DUST].hasItem || inventory[STICKS].hasItem)
                    && (inventory[BED_POSTS].hasItem || inventory[CHOPPED_LOGS].hasItem))
                {   std::cout << "\nYou have successfully made a fire." << std::endl;
                    madeFire = true;
                }
                else
                {   std::cout << "\nYou don't have the right materials for making a fire yet." << std::endl;
                }
                break;
            }

            case 8:
            {   // The player cooks something if they have the right items
                if(madeFire)
                {   if(inventory[FISH].hasItem)
                    {   std::cout << "\nYou successfully cook your walleye over the fire by laying it on\n"
                                  << "an old grate covering the fire pit. The fish provides you with some\n"
                                  << "much needed sustanance." << std::endl;
                        hasEaten = true;
                        inventory[FISH].hasItem = false;
                        numInventory--;
                    }
                    else if(inventory[NOODLES].hasItem && inventory[POT].hasItem && inventory[WATER_JUG].hasItem
                        && inventory[EGGS].hasItem)
                    {   std::cout << "\nYou attempt to cook ramen noodles with eggs in them." << std::endl;
                        if(inventory[COOKBOOK].hasItem)
                        {   std::cout << "Using the cookbook you successfully cook a great pot\n"
                                      << "of noodles. Your hunger is satiated." << std::endl;
                            hasEaten = true;
                            inventory[NOODLES].hasItem = false;
                            inventory[EGGS].hasItem = false;
                            numInventory -= 2;
                        }
                        else
                        {   std::cout << "With no cookbook to guide you, your noodles and eggs are\n"
                                      << "completely unedible. You hope you can find something else in\n"
                                      << "the area to help you get your energy level up." << std::endl;
                            inventory[NOODLES].hasItem = false;
                            inventory[EGGS].hasItem = false;
                            numInventory -= 2;
                        }
                    }
                    else
                    {   std::cout << "\nYou have nothing edible to cook." << std::endl;
                    }
                }
                else
                {   std::cout << "\nYou need a fire in order to cook something." << std::endl;
                }
                break;
            }

            case 9:
            {   // The player practices archery if they have a bow, arrows, and a target
                if(inventory[BOW].hasItem && inventory[ARROWS].hasItem && inventory[TARGET].hasItem)
                {   int practiceRoll = rand() % 25 + 1;
                    archerySkill += practiceRoll;
                    if(archerySkill > 100)
                    {   archerySkill = 100;
                    }
                    std::cout << "\nYou set the target up against a tree and shoot a few arrows at it.\n"
                              << "Your archery skill has increased by " << practiceRoll << " and is now\n"
                              << archerySkill << ". Your practice session only took about 1 minute." 
                              << std::endl;
                    turn--;
                }
                else
                {   std::cout << "\nYou don't have the right equipment to practice archery." << std::endl;
                }
                break;
            }   

            case 10:
            {   // The player practices hand-to-hand combat if they have a life jacket to wrap
                // around a tree to act as a punching bag
                if(inventory[LIFE_JACKET].hasItem)
                {   int practiceRoll = rand() % 25 + 1;
                    handToHand += practiceRoll;
                    if(handToHand > 100)
                    {   handToHand = 100;
                    }
                    std::cout << "\nYou deliver some well-focused punches, kicks, and jabs to your makeshift\n"
                              << "punching bag. Your hand-to-hand combat skill has increased by "
                              << practiceRoll << " and is now " << handToHand << ".\n"
                              << "Your practice session only took about 1 minute." << std::endl;
                    turn--;
                }
                else
                {   std::cout << "\nYou don't have the right equipment to practice hand-to-hand combat."
                              << std::endl;
                }
            }
        }
    }while(choice != 4);    // Loop until user selects 4 to move out of the campfire space
}

/*******************************************************************************
*                           Campfire::printMenu                                *
* This function prints the user's options for different actions to take in the *
* Campfire space.                                                              *
*******************************************************************************/
int Campfire::printMenu(Space *playerLoc)
{   int choice;     // Holds the user's menu choice

    std::cout << "\nLooking around the campfire you see the following items:\n";
    playerLoc->printItems();
    std::cout << "There are some nice straight trees around. You could practice archery if\n"
              << "you had that hunting bow you saw, arrows, and a target. You could practice your\n"
              << "hand-to-hand combat skills if you had something soft to tie around the tree\n"
              << "and punch. There is also a nice firepit where a fire could be made if you had\n"
              << "the right materials." << std::endl;
    std::cout << "\n\tWhat would you like to do next?\n\n"
              << "1. Pick up an item.\n"
              << "2. Drop an item.\n"
              << "3. Move to the space to the top.\n"
              << "4. Move to the space to the bottom.\n"
              << "5. Move to the space to the left.\n"
              << "6. Move to the space to the right.\n"
              << "7. Make a fire.\n"
              << "8. Cook something.\n"
              << "9. Practice archery.\n"
              << "10. Practice hand-to-hand combat.\n\n"
              << "Please make a selection: ";

    choice = getInteger();

    while(choice < 1 || choice > 10)
    {   std::cout << "The only valid choices are 1-10. Please re-enter: ";
        choice = getInteger();
    }

    return choice;
}

/*******************************************************************************
*                           Campfire::printMap                                 *
* This function prints the player's location on the map.                       *
*******************************************************************************/
void Campfire::printMap(Space *playerLoc)
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
        << "   /   \\  |            O        /         |           |__|  \\        /|\\       /   \\    \n"
        << "  /     \\             -|-       |         |           |  |  |        /|\\      /     \\   \n"
        << " / Boat  \\            / \\       |     ----|           |__|  |        /|\\     / Tool  \\  \n"
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
        << " ~           ~   |       |         ~               ~                 ~            ~     \n"
        << "      ~          |       |    ~              ~             ~              ~          ~  \n"
        << "  ~           ~  |       |        ~               ~                ~               ~    \n"
        << "     ~      ~    |       |     ~             ~           ~                  ~          ~\n"
        << "          ~      ---------            ~            ~                    ~               \n"
        << "   ~                       ~                   ~                                 ~      \n"
        << std::endl;
}
