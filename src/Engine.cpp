#include "main.hpp"
#include <iostream>

TCODRandom * rng=new TCODRandom(-42, TCOD_RNG_CMWC);
int CHUNK_SIZE = 128;
//The width and height of the area of active chunks
int ACTIVE_CHUNK_SIZE = 3;

Engine::Engine() 
{
    gui = new Gui();
    is_paused = false;
    player = new PlayerObject(0,0);
    player->ai = new PlayerAI();
    activeChunks = new ActiveChunks(ACTIVE_CHUNK_SIZE);
}

Engine::~Engine()
{
    delete gui;
}

//Input relating to the GUI and general game functions; input relating
//to the player object is handled seperately (see Ai.cpp)
void Engine::handleKeys()
{
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
    switch(lastKey.vk)
    {
        case TCODK_ESCAPE :
            exit(0);
        case TCODK_SPACE :
            if (is_paused == true)
            {
                is_paused = false;
                gui->togglePauseDisplay();
            }
            else
            {
                is_paused = true;
                gui->togglePauseDisplay();
            }
        case TCODK_CHAR :
            handleActionKey(lastKey.c);
            break;
        default:break;
    }

}

void Engine::handleActionKey(int ascii)
{
    switch(ascii)
    {
        case 'l'://Toggle right panel
        {
            gui->toggleRightPanel();
            break;
        }
        default:break;
    }
}

void Engine::update() 
{
    player->ai->update(player);
    gui->camera->posX = player->posX;
    gui->camera->posY = player->posY;
    gui->render();
}
