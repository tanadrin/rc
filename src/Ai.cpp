#include "main.hpp"

//Handles input for the player character only (GUI input handled seperately)
void PlayerAI::update(GameObject *owner)
{
    int dx=0, dy=0;
    switch(engine.lastKey.vk)
    {
        case TCODK_UP: dy=-1; break;
        case TCODK_DOWN: dy=1; break;
        case TCODK_LEFT: dx=-1; break;
        case TCODK_RIGHT: dx=1; break;
        default:break;
    }
    owner->move(dx, dy);
}
