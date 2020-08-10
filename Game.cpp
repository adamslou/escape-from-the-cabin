/*******************************************************************************
** Program name: Game.cpp
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
#include <iostream>
#include <string>
#include "menu.hpp"
#include "getInteger.hpp"
#include "Game.hpp"
#include "Loft.hpp"
#include "Kitchen.hpp"
#include "LivingRoom.hpp"
#include "BoatShed.hpp"
#include "Shore.hpp"
#include "ToolShed.hpp"
#include "Campfire.hpp"
#include "Dock.hpp"

/*******************************************************************************
 *                  Game::Game Default Constructor                             *
 * This function initializes the variables numInventory, fatigued, hasEaten,   *
 * archerySkill, handToHand, canoeFixed, senseOfDirection, repairChance, and   *
 * fishingSkill. It also dynamically instantiates all of the derived Space     *
 * objects for the game, sets the direction pointers so the spaces are         *
 * connected, initializes the player's inventory to empty, and sets the        *
 * player's starting location to the loft space.                               *
 ******************************************************************************/
Game::Game() 
    : numInventory {0}, fatigued {false}, hasEaten {false}, archerySkill {25}, handToHand {25},
      canoeFixed {false}, senseOfDirection {25}, repairChance {25}, fishingSkill {25}
{   // Instantiate all the derived Space objects
    loft = new Loft();
    kitchen = new Kitchen();
    livingRoom = new LivingRoom();
    boatShed = new BoatShed();
    shore1 = new Shore();
    shore2 = new Shore();
    shore3 = new Shore();
    toolShed = new ToolShed();
    campfire = new Campfire();
    dock = new Dock();

    // Connect all spaces with pointers
    loft->setTop(nullptr);
    loft->setLeft(nullptr);
    loft->setRight(nullptr);
    loft->setBottom(livingRoom);
    livingRoom->setTop(loft);
    livingRoom->setBottom(nullptr);
    livingRoom->setLeft(kitchen);
    livingRoom->setRight(nullptr);
    kitchen->setTop(nullptr);
    kitchen->setBottom(shore2);
    kitchen->setLeft(nullptr);
    kitchen->setRight(livingRoom);
    boatShed->setTop(nullptr);
    boatShed->setBottom(nullptr);
    boatShed->setLeft(nullptr);
    boatShed->setRight(shore1);
    shore1->setTop(campfire);
    shore1->setBottom(dock);
    shore1->setLeft(boatShed);
    shore1->setRight(shore2);
    shore2->setTop(kitchen);
    shore2->setBottom(nullptr);
    shore2->setLeft(shore1);
    shore2->setRight(shore3);
    shore3->setTop(nullptr);
    shore3->setBottom(nullptr);
    shore3->setLeft(shore2);
    shore3->setRight(toolShed);
    toolShed->setTop(nullptr);
    toolShed->setBottom(nullptr);
    toolShed->setLeft(shore3);
    toolShed->setRight(nullptr);
    campfire->setTop(nullptr);
    campfire->setBottom(shore1);
    campfire->setLeft(nullptr);
    campfire->setRight(nullptr);
    dock->setTop(shore1);
    dock->setBottom(nullptr);
    dock->setLeft(nullptr);
    dock->setRight(nullptr);

    // Initialize variable for player location
    playerLoc = loft;

    // Add items to inventory
    inventory = {Item(ROPE, "rope", false), 
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
 *                          Game::~Game Destructor                             *
 * This function deallocates dynamically allocated memory for derived Space    *
 * objects.                                                                    *
 ******************************************************************************/
Game::~Game()
{   delete loft;
    delete kitchen;
    delete livingRoom;
    delete boatShed;
    delete shore1;
    delete shore2;
    delete shore3;
    delete toolShed;
    delete campfire;
    delete dock;
}

// Getters
Space * Game::getPlayerLoc()
{   return playerLoc;
}

bool Game::getFatigued()
{   return fatigued;
}

// Setters
void Game::setPlayerLoc(Space *p)
{   playerLoc = p;
}

void Game::setFatigued(bool f)
{   fatigued = f;
}

/*******************************************************************************
 *                          Game::start                                        *
 * This function starts the Escape from McFarland game. The beginning story is *
 * displayed and the user's choices for action are displayed by calling        *
 * startMenu. Then the play function is called with the number of turns to be  *
 * played as the argument. The number of turns depends on the user's actions   *
 * at the start of the game.                                                   *
 ******************************************************************************/
void Game::start()
{   int choice;     // Store's the user's menu choice
    int numTurns = 55;

    std::cout << "\nYou wake up with your hands and feet tied to the bedposts. Your head throbs as\n"
              << "if you took a vicious blow with a club or some other blunt instrument. It\n"
              << "appears you're in some kind of old delapidated cabin, in the loft. You get a\n"
              << "sickening feeling in your stomach as looking towards the front of the cabin\n"
              << "you see the head of what looks to be at least a 12-point buck mounted on the\n"
              << "wall, his eyes looking right at you. Then you hear a voice, that which must\n"
              << "certainly belong to one of your captors.\n\n\"C'mon. Let's move!\" \"Are ya sure\n"
              << "one o' us shouldn't stay 'ere n'case she wakes up?\" \"Nah, she'll be out at\n"
              << "least 'til mid-mornin' c'nsiderin' 'ow hard I smacked 'er.\" \"Fine, I'll do\n"
              << "'er in good if she tries t'get 'way though.\" \"She's got it comin' to 'er\n"
              << "any'ow, heh heh!\" \"I s'pose it'll be alright. We'll only b'gone for an hour.\"\n\n"
              << "Your captors leave and as you squint your eyes looking through the front\n"
              << "window of the cabin, you can make out a small motor boat pulling away from\n"
              << "the shore. 5 minutes later the cloudiness of your mind clears away and a\n"
              << "determination to act sets in. You estimate 55 minutes until your captors'\n"
              << "return." << std::endl;
    do
    {   choice = startMenu();

        switch(choice)
        {   case 1:
            {   std::cout << "\nYou try to wriggle out of the ropes desperately but they are tied\n"
                          << "too tightly. You spend 5 minutes of precious time in your fruitless\n"
                          << "attempt." << std::endl;
                numTurns -= 5;
                break;
            }

            case 2:
            {   std::cout << "\nYou pull on the ropes with all your might. The old rickety bed creaks\n"
                          << "and groans and finally caves in with the bed posts breaking right off\n"
                          << "the bed frame. With your arms now free you are able to untie the ropes\n"
                          << "from your wrists and ankles. You are now able to move freely. You also\n"
                          << "notice that you feel quite famished. If you don't get something to eat\n"
                          << "soon, your movement will likely become twice as slow. You also notice an\n"
                          << "old gunny sack on the floor that you can use to carry around anything \n"
                          << "that you might find useful. You estimate that it can hold around 8 items\n"
                          << "of average size." << std::endl; 
                break;
            }

            case 3:
            {   std::cout << "\nYou scream at the top of your lungs for help. You hear nothing in response.\n"
                          << "A precious 5 minutes of time has been wasted." << std::endl;
                numTurns -= 5;
            }
        }
    }while(choice != 2);    // Loop until user selects 2 which will advance the game past the start

    // Call the play function to start the game
    if(numTurns > 0)
    {   play(numTurns);
    }
    else
    {   std:: cout << "\nYour captors have returned and any chance at escape is gone. Your end has\n"
                   << "come, though it will not come quickly or peacefully..." << std::endl;
    }
}

/*******************************************************************************
*                           Game::startMenu                                    *
* This function prints the user's options for different actions to take at the *
* start of the game.                                                           *
*******************************************************************************/
int Game::startMenu()
{   int choice;     // Holds the user's menu choice

    std::cout << "\n\tWhat would you like to do next?\n\n"
              << "1. Try to wriggle out of the ropes tied around your wrists and ankles.\n"
              << "2. Pull on the ropes as hard as you can.\n"
              << "3. Scream for help.\n\n"
              << "Please make a selection: ";

    choice = getInteger();

    while(choice < 1 || choice > 3)
    {   std::cout << "The only valid choices are 1-3. Please re-enter: ";
        choice = getInteger();
    }

    return choice;
}

/*******************************************************************************
 *                              Game::play                                     *
 * This function facilitates gameplay for a number of turns 55 or less,        *
 * depending on the user's actions at the start of the game. Each turn         *
 * represents a minute. Once time runs out the game is over. Each turn the     *
 * takeTurn function is called on the derived Space object where the player    *
 * character is located. The player's inventory is passed to the takeTurn      *
 * function, along with the number of turns remaining and the player location. *
 * The numTurns variable is decremented by 1 at the end of the turn and by 2   *
 * if the player is fatigued, indicating that the player's movements are       *
 * taking twice as long due to the fatigue.                                    *
 ******************************************************************************/
void Game::play(int numTurns)
{   int turn = numTurns;                    // The number of turns will be 55 or less and then decrease
    bool returnEarlyEventFinished = false;  // Keeps track of whether this event has happened yet

    while(turn > 0 && turn < 100)
    {   // Call printMap and takeTurn for every turn. These functions will be overridden by
        // a derived Space class, depending on which space the player is in
        playerLoc->printMap(playerLoc);  // Display map at the start of the turn
        playerLoc->takeTurn(inventory, numInventory, turn, playerLoc, hasEaten, archerySkill,
                            handToHand, canoeFixed, senseOfDirection, repairChance, fishingSkill);    

        // With 20 min left (turn = 20) one of the captors returns early
        if(turn <= 20 && !returnEarlyEventFinished)
        {   returnEarlyEvent(turn);
            setPlayerLoc(shore1);
            returnEarlyEventFinished = true;
        }

        // Player becomes fatigued if she hasn't eaten and there are only 20 rounds left
        if(turn <= 20 && !hasEaten)
        {   fatigued = true;
        }

        if(hasEaten)
        {   fatigued = false;
        }

        if(!fatigued)
        {   turn--;
        }
        else
        {   turn -= 2;  // Decrement twice as fast if player is fatigued
        }
    }
    
    // Once turn = 0, the game is over
    if(turn <= 0)
    {   std::cout << "\nYour captors have returned and any chance at escape is gone. Your end has\n"
                  << "come, though it will not come quickly or peacefully..." << std::endl;
    }
    else
    {   std::cout << "\nCongratulations on escaping McFarland!" << std::endl;
    }
}

/*******************************************************************************
 *                          Game::returnEarlyEvent                             *
 * This function has one of the captors returning early. The player then must  *
 * choose how to fight the captor: hand to hand, with a bow and arrows, or     *
 * with an axe. There is a random attack roll which is compared to the player's*
 * hand-to-hand skill, archery skill, or in the case of the axe the value 50,  *
 * meaning if the player chooses to fight with the axe, they will have a       *
 * 50-50 chance of winning the fight. The function takes the int turn by       *
 * by reference as a parameter. If the player loses the fight, turn is         *
 * decreased enough that the game is over. If the player wins, the game        *
 * resumes from where it left off.                                             *
 ******************************************************************************/
void Game::returnEarlyEvent(int &turn)
{   std::cout << "\nAs you explore the cabin and its surroundings you suddenly hear the sound of a\n"
              << "motorboat coming your way. You quickly move towards the shore area and your heart\n"
              << "sinks as you realize that one of your captors has returned early, probably to\n"
              << "check up on you. You will have to try and fight him off." << std::endl;
    std::cout << "\n\tHow would you like to fight?\n\n"
              << "1. Hand to hand.\n"
              << "2. Use a bow and arrows.\n"
              << "3. Use an axe.\n\n"
              << "Please make a selection: ";
    int choice = getInteger();
    while(choice < 1 || choice > 3)
    {   std::cout << "Please enter a number from 1 to 3: ";
        choice = getInteger();
    }

    int attackRoll = rand() % 100 + 1;

    // Player chooses to fight hand to hand
    if(choice == 1)
    {   if(attackRoll <= handToHand)
        {   std::cout << "\nYou crouch down behind a shrub near the shore and wait for the man to walk off\n"
                      << "the dock. As he does you pounce on him and land a crushing blow to his left\n"
                      << "jaw followed by a vicious roundhouse kick to his right kidney. He stumbles\n"
                      << "backwards and into his boat again and quickly makes off. You can expect him\n"
                      << "to return with his partner in around 20 minutes. You better not be here when\n"
                      << "they return..." << std::endl;
        }
        else
        {   std::cout << "\nYou crouch down behind a shrub near the shore and wait for the man to walk off\n"
                      << "the dock. As he does you pounce on him but your feeble attempt barely affects\n"
                      << "the much larger sturdily-built man. He quickly subdues you. You have no chance\n"
                      << "of escape this time." << std::endl;
            turn -= 50;
        }
    }

    // Player chooses to fight with a bow and arrows
    else if(choice == 2)
    {   if(inventory[BOW].hasItem && inventory[ARROWS].hasItem)
        {   if(attackRoll <= archerySkill)
            {   std::cout << "\nYou crouch down behind a shrub near the shore and wait for the man to get out\n"
                          << "of his boat. As he's stepping onto the dock you plug an arrow into his right\n"
                          << "kidney. He falls back into the boat and quickly hits the gas for the motor.\n"
                          << "You can expect him to return with his partner in around 20 minutes. You better\n"
                          << "not be here when they return..." << std::endl;
            }
            else
            {   std::cout << "\nYou crouch down behind a shrub near the shore and wait for the man to get out\n"
                          << "of his boat. As he's stepping onto the dock you shoot an arrow at him which\n"
                          << "wildly misses and slips into the water of the lake behind the man. The man\n"
                          << "quickly covers the distance between you two and subdues you. You have no\n"
                          << "chance of escape this time." << std::endl;
                turn -= 50;
            }
        }
        else
        {   std::cout << "\nYou frantically search for the bow and arrows but by the time you realize\n"
                      << "you don't have them in your gunny sack the man has already leapt onto the\n"
                      << "dock, covered the distance between you two, and subdued you easily. You\n"
                      << "have no chance of escape this time." << std::endl;
            turn -= 50;
        }
    }

    // Player chooses to fight with the axe
    else
    {   if(inventory[AXE].hasItem)
        {   if(attackRoll <= 50)
            {   std::cout << "\nYou crouch down behind a shrub near the shore and wait for the man to walk\n"
                          << "off the dock. As he does you swing wildly with your axe. Although you miss\n"
                          << "his body the downward stroke plants the axe blade right across his left foot.\n"
                          << "You can see that the man's big toe has been severed and the stump is oozing\n"
                          << "blood. The man screams in agony, runs back to his boat, falls in, and hits\n"
                          << "the gas. You can expect him to return with his partner in around 20 minutes.\n"
                          << "You better not be here when they return..." << std::endl;
            }
            else
            {   std::cout << "\nYou crouch down behind a shrub near the shore and wait for the man to walk\n"
                          << "off the dock. As he does you swing wildly with your axe. You miss\n"
                          << "completely as the axe if much too large and unwieldy for a small woman\n"
                          << "such as yourself. The man quickly wrestles the axe from your hands and\n"
                          << "subdues you. You have no chance of escape this time." << std::endl;
                turn -= 50;
            }
        }
        else
        {   std::cout << "\nYou frantically search for the axe but by the time you realize\n"
                      << "you don't have it in your gunny sack the man has already leapt onto the\n"
                      << "dock, covered the distance between you two, and subdued you easily. You\n"
                      << "have no chance of escape this time." << std::endl;
            turn -= 50;
        }
    }
}
